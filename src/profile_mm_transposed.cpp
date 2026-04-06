#include "../includes/baseline.h"
#include "../includes/baseline_tests.h"
#include "../includes/profile_mm_transposed.h"
#include <iostream>


void run_profile_mm_transposed() {
    const int n = 256;
    const int repetitions = 20;

    double* A = new double[n * n];
    double* B = new double[n * n];
    double* C = new double[n * n];

    for (int i = 0; i < n * n; ++i) {
        A[i] = (i % 100) * 0.1;
        B[i] = (i % 100) * 0.2;
        C[i] = 0.0;
    }

    double* B_transposed = transpose_row_major(B, n, n);

    for (int rep = 0; rep < repetitions; ++rep) {
        multiply_mm_transposed_b(A, n, n, B_transposed, n, n, C);
    }

    std::cout << C[0] << std::endl;

    delete[] A;
    delete[] B;
    delete[] B_transposed;
    delete[] C;
}