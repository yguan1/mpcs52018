#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1000

double x[N][N];
double y[N][N];
double z[N][N];

double timer(void){
  struct timeval time;
  gettimeofday(&time, 0);
  return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char **argv){
  int i,j,k;
  double r;
  double ts,tf;


  
  /* initialize y, z */
  for (i=0;i<N;++i){
    for (j=0;j<N;++j){
      y[i][j] = 1;
      z[i][j] = 1;
    }
  }

  ts = timer();
  for (i=0;i<N;++i){
    for (j=0;j<N;++j){
      r = 0;
      for (k=0;k<N;++k)
	r += y[i][k]*z[k][j];
      x[i][j] = r;
    }
  }
  tf = timer();

  printf("%f %f(s)\n", x[0][0],tf-ts);
}
