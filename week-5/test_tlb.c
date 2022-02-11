#include<stdio.h>
#include<stdlib.h>
#include<papi.h>

void handle_error(int errcode);


double timer(void){
  struct timeval time;
  gettimeofday(&time, 0);
  return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char **argv){
    double *a;
    long  i, n, stride;
    int ret;
    double d = 0.0;

    if (argc != 3){
        printf("usage: a.out n stride \n");
        abort();
    }

    n = atoi(argv[1]);                        /* vector length */
    stride = atoi(argv[2]);                   /* loop stride */

    a = (double *) malloc(n*stride*sizeof(double));  

    for (i=0;i<n*stride;++i)
    a[i] = -1;

    ts = timer();
    ret = PAPI_hl_region_begin("daxpy");
    if ( ret != PAPI_OK )
        handle_error(1);


    for (i=0;i<n*stride;i+=stride)
        d += a[i];

    ret = PAPI_hl_region_end("daxpy");
    tf = timer();
    if ( ret != PAPI_OK )
        handle_error(ret);


    printf("%f\n", d);

    printf("clock time: %f(s)\n",tf-ts);
    return 0;
}

void handle_error (int retval){
    printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
    exit(1);
}