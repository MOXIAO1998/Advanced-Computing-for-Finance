#include <iostream>
#include "../includes/baseline_tests.h"
#include "../includes/optimized.h"
using namespace std;


void multiply_mm_blocked(const double* matrixA, int rowsA, int colsA,
const double* matrixB, int rowsB, int colsB,
double* result) {
    if (matrixA == nullptr || matrixB == nullptr || result == nullptr) {
        cout << "Null pointer input in multiply_mm_blocked." << std::endl;
        return;
    }
    if (rowsA <= 0 || colsA <= 0 || rowsB <= 0 || colsB <= 0) {
        cout << "Invalid dimensions in multiply_mm_blocked." << std::endl;
        return;
    }
    if (colsA != rowsB) {
        cout << "Number of columns of A does not equal number of rows of B." << std::endl;
        return;
    }

    const int BLOCK = 32;

    for (int i = 0; i < rowsA * colsB; ++i) {
        result[i] = 0.0;
    }

    for (int ii = 0; ii < rowsA; ii += BLOCK) {
        for (int kk = 0; kk < colsA; kk += BLOCK) {
            for (int jj = 0; jj < colsB; jj += BLOCK) {

                int i_end = min(ii + BLOCK, rowsA);
                int k_end = min(kk + BLOCK, colsA);
                int j_end = min(jj + BLOCK, colsB);

                for (int i = ii; i < i_end; ++i) {
                    for (int k = kk; k < k_end; ++k) {
                        double a_ik = matrixA[i * colsA + k];
                        for (int j = jj; j < j_end; ++j) {
                            result[i * colsB + j] += a_ik * matrixB[k * colsB + j];
                        }
                    }
                }
            }
        }
    }
}

void test_mm_blocked() {
    int rowsA = 2, colsA = 3;
    int rowsB = 3, colsB = 4;

    double* A = new double[6]{
        1, 2, 3,
        4, 5, 6
    };

    double* B = new double[12]{
        7, 8, 9, 10,
        11, 12, 13, 14,
        15, 16, 17, 18
    };

    double* result = new double[8];

    double expected[8]{
        74, 80, 86, 92,
        173, 188, 203, 218
    };

    multiply_mm_blocked(A, rowsA, colsA, B, rowsB, colsB, result);

    cout << "test_mm_blocked: "
              << (check_matrix(result, expected, rowsA, colsB) ? "PASS" : "FAIL")
              << endl;

    delete[] A;
    delete[] B;
    delete[] result;
}

void run_optimized_black() {
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
        multiply_mm_blocked(A, n, n, B, n, n, C);
    }

    std::cout << C[0] << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

}