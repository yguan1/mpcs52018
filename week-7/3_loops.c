#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/time.h>
#include<papi.h>

void handle_error(int errcode){
  char error_str[PAPI_MAX_STR_LEN];
  //  PAPI_perror(errcode,error_str,PAPI_MAX_STR_LEN);
  fprintf(stderr,"PAPI_error in call to create_eventset %d: %s\n",errcode,error_str);
  exit(1);
}

double timer(void){
  struct timeval time;
  gettimeofday(&time, 0);
  return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char **argv){


  double ts,tf;
  int ret;
  int i;
  double x;
  long n = 10000000;
   ts = timer();
  ret = PAPI_hl_region_begin("loop1");
  if ( ret != PAPI_OK )
    handle_error(1);
 
  for (int i=0;i<n;++i){
    x +=1;
    }
  tf = timer();
  ret = PAPI_hl_region_end("loop1");
  if ( ret != PAPI_OK )
    handle_error(ret);
tf = timer();
  printf("loop 1: %f(s)\n", tf-ts);
ts = timer();
  ret = PAPI_hl_region_begin("loop2");
  if ( ret != PAPI_OK )
    handle_error(1);
  
  for (int i=0;i<n;++i){
  if (i < n/2)
   x +=1;
  else
   x -=1;
 }

  
  ret = PAPI_hl_region_end("loop2");
  if ( ret != PAPI_OK )
    handle_error(ret);
tf = timer();
  printf("loop 2: %f(s)\n", tf-ts);
    ts = timer();
  ret = PAPI_hl_region_begin("loop3");
  if ( ret != PAPI_OK )
    handle_error(1);
  
  for (int i=0;i<n;++i){
  if (rand() < .5)
   x +=1;
  else
   x -=1;
 }
  
  ret = PAPI_hl_region_end("loop3");
  if ( ret != PAPI_OK )
    handle_error(ret);
tf = timer();
  printf("loop 3: %f(s)\n", tf-ts);
}
