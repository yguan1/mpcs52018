#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <papi.h>

double mat_mul(int ops){
    // Need to initialise differently otherwise compiler might optimise away
    int i, j, k;
    int M = 12, N = 32, K = 192;
    double A[M][K];
    double B[K][N];
    double C[M][N];
    double ts,tf;
    int ret
    int loops=ops/10;          // We have 10 floating point operations inside the loop

    for (i = 0; i < M; ++i){
        for (j = 0; j < K; ++j){
            A[i][j] = M_PI;
        }
    }

    for (i = 0; i < K; ++i){
        for (j = 0; j < N; ++j){
            B[i][j] = M_2_PI;
        }
    }

    ts = timer();
    ret = PAPI_hl_region_begin("loop");
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j += 4) {
            for (k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j + 1] += A[i][k] * B[k][j + 1];
                C[i][j + 2] += A[i][k] * B[k][j + 2];
                C[i][j + 3] += A[i][k] * B[k][j + 3];
            }
        }
    }

    ret = PAPI_hl_region_end("loop");
    tf = timer();

    printf("clock time: %f(s)\n",tf-ts);

    return C
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

    mat_mul(n)

    return EXIT_SUCCESS;
}