#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <papi.h>

double timer();

double mat_mul(int ops){
    // Need to initialise differently otherwise compiler might optimise away
    int i, j, k;
    int M = 2048, N = 1024, K = 512;
    double** A = (double **)malloc(M * sizeof(double*));
    for(int i = 0; i < M; i++) 
	A[i] = (double *)malloc(K * sizeof(double));
    double** B = (double **)malloc(K * sizeof(double*));
    for(int i = 0; i < K; i++)
        B[i] = (double *)malloc(N * sizeof(double));
    double** C = (double **)malloc(M * sizeof(double*));
    for(int i = 0; i < M; i++)
        C[i] = (double *)malloc(N * sizeof(double));
    double ts,tf;
    int ret;
    int iter;
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


    ret = PAPI_hl_region_begin("loop");
    ts = timer();

    for (iter = 0; iter < loops; iter++) { 
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j += 16) {
                for (k = 0; k < K; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                    C[i][j + 1] += A[i][k] * B[k][j + 1];
                    C[i][j + 2] += A[i][k] * B[k][j + 2];
                    C[i][j + 3] += A[i][k] * B[k][j + 3];
                    C[i][j + 4] += A[i][k] * B[k][j + 4];
                    C[i][j + 5] += A[i][k] * B[k][j + 5];
                    C[i][j + 6] += A[i][k] * B[k][j + 6];
                    C[i][j + 7] += A[i][k] * B[k][j + 7];
                    C[i][j + 8] += A[i][k] * B[k][j + 8];
                    C[i][j + 9] += A[i][k] * B[k][j + 9];
                    C[i][j + 10] += A[i][k] * B[k][j + 10];
                    C[i][j + 11] += A[i][k] * B[k][j + 11];
                    C[i][j + 12] += A[i][k] * B[k][j + 12];
                    C[i][j + 13] += A[i][k] * B[k][j + 13];
                    C[i][j + 14] += A[i][k] * B[k][j + 14];
                    C[i][j + 15] += A[i][k] * B[k][j + 15];
                    /* C[i][j + 16] += A[i][k] * B[k][j + 16];
                    C[i][j + 17] += A[i][k] * B[k][j + 17];
                    C[i][j + 18] += A[i][k] * B[k][j + 18];
                    C[i][j + 19] += A[i][k] * B[k][j + 19];
                    C[i][j + 20] += A[i][k] * B[k][j + 20];
                    C[i][j + 21] += A[i][k] * B[k][j + 21];
                    C[i][j + 22] += A[i][k] * B[k][j + 22];
                    C[i][j + 23] += A[i][k] * B[k][j + 23];
                    C[i][j + 24] += A[i][k] * B[k][j + 24];
                    C[i][j + 25] += A[i][k] * B[k][j + 25];
                    C[i][j + 26] += A[i][k] * B[k][j + 26];
                    C[i][j + 27] += A[i][k] * B[k][j + 27];
                    C[i][j + 28] += A[i][k] * B[k][j + 28];
                    C[i][j + 29] += A[i][k] * B[k][j + 29];
                    C[i][j + 30] += A[i][k] * B[k][j + 30];
                    C[i][j + 31] += A[i][k] * B[k][j + 31]; */

                }
            }
        }
    }

    tf = timer();
    ret = PAPI_hl_region_end("loop");

    printf("clock time: %f(s)\n",tf-ts);

    return C[0][0];
}

double timer(void){
    struct timeval time;
    gettimeofday(&time, 0);
    return time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: %s <num>\n", argv[0]);
        printf("number of operations: <num> millions\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]) * 10;
    if (n<=0)
        n=1000;

    mat_mul(n);

    return EXIT_SUCCESS;
}
