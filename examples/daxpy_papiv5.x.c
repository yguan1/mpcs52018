#include<stdio.h>
#include<stdlib.h>
#include<papi.h>
#include<string.h>



void handle_error(int errcode);
void doit(double *a, double *b, double *c, int n);

main(int argc, char **argv)
{
  double *a,*b,*c;                /* daxpy arrays */
  int *r;                         /* vector of random indices for random lookups */
  double alpha = 1.2;             /* daxpy const */
  int  i, count, n, stride;       /* looping vars */
  int num_events;                 /* number of PAPI events */
  char *event_name;               /* string name for PAPI event */

  /* Array of PAPI Events measured in a given execution. 
     Combination must be admissable and events must exist on
     the given platform. Use papa_avail to get event listing 
  */
  int Events[] = {PAPI_TLB_DM};
  //int Events[] = {PAPI_LD_INS,  PAPI_L1_LDM, PAPI_L2_LDM};
  //int Events[] = { PAPI_FP_INS,PAPI_TOT_CYC, PAPI_L1_DCM};
  //int Events[] = { PAPI_L1_LDM};

  long_long *values;               /* PAPI results array */
  long_long ts, tf;                /* start and end time */
  int ret;
  double cycles_per_sec;           /* GFlops */
  
  if (argc != 3){
    printf("usage: ./daxpy n stride\n");
    abort();
  }

  num_events = sizeof(Events)/sizeof(int);  /* size of event array */
  n = atoi(argv[1]);                        /* vector length */
  stride = atoi(argv[2]);                   /* loop stride */
  event_name = (char *) malloc(128);        /* string name for event, reuse buffer */

  values = (long_long *) malloc(num_events*sizeof(long_long));
  a = (double *) malloc(n*sizeof(double));  /* daxpy vectors */
  b = (double *) malloc(n*sizeof(double));
  c = (double *) malloc(n*sizeof(double));
  r = (int *) malloc(n*sizeof(int));        /* random indices, precompute to avoid cache pollution */

  srand(time(NULL));                        /* Initialization, should only be called once.  */
  for (i=0;i<n;++i){
    a[i] = -1;
    b[i] = 1;
    r[i] =  rand()%(n-1);    
  }


  /* Start counting events */
  if ((ret=PAPI_start_counters(Events, num_events)) != PAPI_OK)
    handle_error(ret);

  ts = PAPI_get_real_usec();        /* start timer */

  /* daxpy with arbitrary stride */

  count = 0; 

  for (i=0;i<n;i+=stride,++count) 
    c[i] = a[i] + alpha*b[i];

  /* "daxpy" with random stride */
  /*
  while (count < n){                         
    c[r[count]] = a[r[count]] + alpha*b[r[count]];
    ++count;
  }
  */
  tf = PAPI_get_real_usec();        /* end timer */

  if ((ret=PAPI_stop_counters(values, num_events)) != PAPI_OK)
    handle_error(ret);

  printf("total iterations of daxpy: %d\n", count);

  for (i=0;i<num_events;++i){       /* print name/value of each event counter */
    PAPI_event_code_to_name(Events[i],event_name);
    printf("%s:%lld\n", event_name, values[i]);
    if (strcmp(event_name,"PAPI_TOT_CYC") == 0){
      cycles_per_sec = (double) values[i]/(double) ((tf-ts)*1.e-6);
      printf("cycles per second: %e\n", cycles_per_sec);
    }
  }
  printf("tot time: %e  result: %f\n", (tf-ts)/1.e6, c[0]);
  printf("L1 hit rate: %f\n", 1. - ((float) values[1])/((float) values[0]));

  double sum = 0;
  for (i=0;i<n;++i)
    sum += c[i];

}



void handle_error(int errcode){
  char error_str[PAPI_MAX_STR_LEN];
  //  PAPI_perror(errcode,error_str,PAPI_MAX_STR_LEN);
  fprintf(stderr,"PAPI_error in call to create_eventset %d: %s\n",errcode,error_str);
  exit(1);
}


 
