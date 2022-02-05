#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<assert.h>
#include <sys/time.h>

void handle_error(int errcode);

double timer(void){
  struct timeval time;
  gettimeofday(&time, 0);
  return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char **argv)
{
  double *a, *b, c=0.0;
  double ts, tf;
  long i,j,n;
  int  iter,niter;
  int  blocksize;
  int  nblocks;
  int  stride;
  int  ret;

  n         = atol(argv[1]);                /* vector length */
  niter     = atoi(argv[2]);                /* number of do products */
  blocksize = atoi(argv[3]);                /* block size for blocked algorithm */
  stride    = atoi(argv[4]);                /* dotp loop stride */

  assert(n%blocksize == 0);                 /* not accomodating remainder blocks */
  nblocks = n/blocksize;

  a = (double *) malloc(n*sizeof(double));  /* daxpy vectors */
  b = (double *) malloc(n*sizeof(double));  /* daxpy vectors */

  for (i=0;i<n;++i){                        /* init vecs */
    a[i] = -1;
    b[i] = -1;
  }

  ts = timer();
  ret = PAPI_hl_region_begin("daxpy_opt");   /* Start counting events */
  if ( ret != PAPI_OK )
    handle_error(1);

  for (j=0;j<nblocks;++j){                   /* blocked algorithm */
    int lo=j*blocksize, hi=lo+blocksize-1;
    for (iter=0;iter<niter;++iter){
      for (i=lo;i<=hi;i+=stride){
	c += a[i]*b[i];
      }
    }
  }

  ret = PAPI_hl_region_end("daxpy_opt");
  if ( ret != PAPI_OK )
    handle_error(ret);
  printf("optimized c: %f\n", c);
  tf = timer();
  printf("time(s)%f\n", (tf-ts));

  c=0.;                                       /* reset c for next dot product */
  
  ts = timer();
  ret = PAPI_hl_region_begin("daxpy_naive");  /* Start counting events */
  if ( ret != PAPI_OK )
    handle_error(1);

  for (j=0;j<niter;++j){                      /* regular algorithm */
    for (i=0;i<n;i+=stride){
      c += a[i]*b[i];
    }
  }

  ret = PAPI_hl_region_end("daxpy_naive");
  if ( ret != PAPI_OK )
    handle_error(ret);

  printf("naive c: %f\n", c);
  tf = timer();
  printf("time(s)%f\n", (tf-ts));

  return 0;
}
void handle_error (int retval){
     printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
     exit(1);
}