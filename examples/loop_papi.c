#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <papi.h>

double addmul(double add, double mul, int ops){
   // Need to initialise differently otherwise compiler might optimise away
   double sum1=0.1, sum2=-0.1, sum3=0.2, sum4=-0.2, sum5=0.0;
   double mul1=1.0, mul2= 1.1, mul3=1.2, mul4= 1.3, mul5=1.4;
   int loops=ops/10;          // We have 10 floating point operations inside the loop
   double expected = 5.0*add*loops + (sum1+sum2+sum3+sum4+sum5)
               + pow(mul,loops)*(mul1+mul2+mul3+mul4+mul5);

   for (int i=0; i<loops; i++) {
      mul1*=mul; mul2*=mul; mul3*=mul; mul4*=mul; mul5*=mul;
      sum1+=add; sum2+=add; sum3+=add; sum4+=add; sum5+=add;
   }
   return  sum1+sum2+sum3+sum4+sum5+mul1+mul2+mul3+mul4+mul5 - expected;
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

   double x = M_PI;
   double y = 1.0 + 1e-8;
   
   ts = timer();
   ret = PAPI_hl_region_begin("loop");
   x = addmul(x, y, n);
   ret = PAPI_hl_region_end("loop");
   tf = timer();

   printf("clock time: %f(s)\n", x[0][0],tf-ts);
   
   return EXIT_SUCCESS;
}