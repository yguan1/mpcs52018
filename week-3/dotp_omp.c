#include<stdio.h>
#include<stdlib.h>

#ifdef OMP
#include<omp.h>
#endif

#ifdef PAPI
#include<papi.h>
#endif

#define N 1000000000

int main(int argc, char **argv)
{
  long i;
  int n,nt;
  double sum=0.0;
  double ts, tf;

  double *a = (double *)malloc(N * sizeof(double));
  double *b = (double *)malloc(N * sizeof(double));
  
#ifdef OMP
  nt = atoi(argv[1]);
  omp_set_num_threads(nt);
#endif

  for (i=0;i<N;++i){
    a[i] = 1;
    b[i] = -1;
  }

#ifdef OMP
  ts = omp_get_wtime();
#endif

#ifdef PAPI
  PAPI_hl_region_begin("dotp");
#endif
 
#pragma omp parallel for shared(n,a,b) private(i) reduction(+:sum) 
  for (i=0;i<N;++i){
    sum += a[i]*b[i];
  }
#ifdef PAPI
  PAPI_hl_region_end("dotp");
#endif
#ifdef OMP
  tf = omp_get_wtime();
#endif
 printf("dot product:%f,  time(s)%f\n", sum,(tf-ts));
 free(a);
 free(b);
}


