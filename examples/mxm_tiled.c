#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<papi.h>
#define N 1000
#define MAX( a, b ) ( ( a > b) ? a : b )
#define MIN( a, b ) ( ( a < b) ? a : b )

double x[N][N];
double y[N][N];
double z[N][N];

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
  int i,j,k;
  int ii,jj,kk;
  int B;
  double r;
  long long *values;               /* PAPI results array */
  double ts,tf;
  int Events[] = {PAPI_L1_DCM, PAPI_LD_INS};
  int ret;
  int num_events = sizeof(Events)/sizeof(int);  /* size of event array */
  char *event_name = (char *) malloc(128);        /* string name for event, reuse buffer */
  float rtime, ptime, mflops;
  long long flpops; 
  char *event_name;

  if (argc < 2)
    B = 16;
  else
    B = atoi(argv[1]);

  
  /* initialize y, z */
  for (i=0;i<N;++i){
    for (j=0;j<N;++j){
      y[i][j] = 1;
      z[i][j] = 1;
    }
  }

  if ((ret=PAPI_start_counters(Events, num_events)) != PAPI_OK)
    handle_error(ret);
  PAPI_flops(&rtime, &ptime, &flpops, &mflops);
  ts = timer();
  for (jj=0;jj<N;jj+=B){
    for (kk=0;kk<N;kk+=B){
      for (i=0;i<N;++i){
	for (j=jj;j<MIN(jj+B,N);++j){
	  r = 0;
	  for (k=kk;k<MIN(kk+B,N);++k)
	    r += y[i][k]*z[k][j];
	  x[i][j] += r;
	}
      }
    }
  }
  tf = timer();
  PAPI_flops(&rtime, &ptime, &flpops, &mflops);
  if ((ret=PAPI_stop_counters(values, num_events)) != PAPI_OK)
    handle_error(ret);
  
  for (i=0;i<num_events;++i){       /* print name/value of each event counter */
    PAPI_event_code_to_name(Events[i],event_name);
    printf("%s:%lld\n", event_name, values[i]);
  }
  printf("%f %f(s)\n", x[0][0],tf-ts);
  printf("Number of floatinig point operations = %lld\n",flpops);
  printf("mflops = %f\n",mflops);
}
