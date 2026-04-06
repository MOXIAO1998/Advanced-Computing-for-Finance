#include "../includes/baseline.h"
#include <iostream>
#include "../includes/profile_mm_naive.h"
void run_profile_mm_naive() {
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

    for (int rep = 0; rep < repetitions; ++rep) {
        multiply_mm_naive(A, n, n, B, n, n, C);
    }

    std::cout << C[0] << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

}