#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <papi.h>

double addmul(int ops){
   // Need to initialise differently otherwise compiler might optimise away
   double sum1=0.1, sum2=-0.1, sum3=0.2, sum4=-0.2, sum5=0.0;
   double mul1=1.0, mul2= 1.1, mul3=1.2, mul4= 1.3, mul5=1.4;
   double add1=M_PI, add2=M_2_PI, add3=M_PI_2, add4=M_PI_4, add5=M_1_PI;
   int loops=ops/10;          // We have 10 floating point operations inside the loop

   for (int i=0; i<loops; i++) {
      mul1*=add1; sum1+=add1;
      mul2*=add2; sum2+=add2;
      mul3*=add3; sum3+=add3;
      mul4*=add4; sum4+=add4;
      mul5*=add5; sum5+=add5;

      mul1*=add5; sum1+=add1;
      mul2*=add4; sum2+=add2;
      mul3*=add3; sum3+=add3;
      mul4*=add2; sum4+=add4;
      mul5*=add1; sum5+=add5;

      mul1*=add1; sum1+=add5;
      mul2*=add2; sum2+=add4;
      mul3*=add3; sum3+=add3;
      mul4*=add4; sum4+=add2;
      mul5*=add5; sum5+=add1;

      mul1*=add5; sum1+=add5;
      mul2*=add4; sum2+=add4;
      mul3*=add3; sum3+=add3;
      mul4*=add2; sum4+=add2;
      mul5*=add1; sum5+=add1;
   }
   return 0;
}

double timer(void){
  struct timeval time;
  gettimeofday(&time, 0);
  return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char** argv) {
   double ts,tf;
   int ret
   if (argc != 2) {
      printf("usage: %s <num>\n", argv[0]);
      printf("number of operations: <num> millions\n");
      exit(EXIT_FAILURE);
   }
   int n = atoi(argv[1]) * 1000000;
   if (n<=0)
       n=1000;
   
   ts = timer();
   ret = PAPI_hl_region_begin("loop");
   x = addmul(n);
   ret = PAPI_hl_region_end("loop");
   tf = timer();

   printf("clock time: %f(s)\n",tf-ts);
   
   return EXIT_SUCCESS;
}