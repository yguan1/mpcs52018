#!/bin/csh
set echo on
module load papi/6.0

gcc -O2 -I/usr/local/papi/6.0/include -c 3_loops.c
gcc -O2 -o loop_o2 3_loops.o -L/usr/local/papi/6.0/lib -lpapi

gcc -O0 -I/usr/local/papi/6.0/include -c 3_loops.c
gcc -O0 -o loop_o0 3_loops.o -L/usr/local/papi/6.0/lib -lpapi