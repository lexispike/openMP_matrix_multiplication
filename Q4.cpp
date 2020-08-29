/*
 * Alyxandra Spikerman
 * High Perfomance Computing
 * Homework 3 - Question 4
 *
 */

#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    int N = 1000;

    srand(150); // seed the random number generator

    int thread_num, processors, max_threads, sum;
    int mat[N][N];
    int vect[N];
    int result[N];

    // initialize values in matrix, vector, and result
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        vect[i] = rand() % 50 + 1;
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 50 + 1;
        }
    }

    // get specs on the processors available to omp and max number of threads available (should be equal)
    processors = omp_get_num_procs();
    max_threads = omp_get_max_threads();
    cout << "Number of processors available: " << processors << endl;
    cout << "Number of max threads: " << max_threads << endl;

    // printed_val is so that we only print the unique thread id once
    bool printed_val[max_threads];
    for (int i = 0; i < max_threads; i++) {
        printed_val[i] = false;
    }

    for (int i = 0; i < N; i++) {
        sum = 0;
        // do the reduction for this row with the sum variable in this parallel loop
        #pragma omp parallel for reduction(+:sum) private(thread_num)
        for (int j = 0; j < N; j++) {
            thread_num = omp_get_thread_num();
            if (!printed_val[thread_num]) { // print the thread num if we haven't already
                cout << "thread " << thread_num << endl;
                printed_val[thread_num] = true;
            }
            sum += mat[i][j] * vect[j]; // reduction
        }
        result[i] = sum; // set the result[row] = sum
    }

    // print the results
    for (int i = 0; i < N; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
