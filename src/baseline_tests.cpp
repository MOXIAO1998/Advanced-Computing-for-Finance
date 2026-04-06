//
// Created by Moxiao Li on 4/5/26.
//

#include "../includes/baseline_tests.h"
#include "../includes/baseline.h"
#include <iostream>
#include <cmath>
#include <chrono>


using namespace std;

bool nearly_equal(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

bool check_vector(const double* actual, const double* expected, int size) {
    for (int i = 0; i < size; ++i) {
        if (!nearly_equal(actual[i], expected[i])) {
            return false;
        }
    }
    return true;
}

bool check_matrix(const double* actual, const double* expected, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        if (!nearly_equal(actual[i], expected[i])) {
            return false;
        }
    }
    return true;
}

// double* row_major_to_col_major(const double* matrix, int rows, int cols) {
//     double* col_major = new double[rows * cols];
//
//     for (int r = 0; r < rows; ++r) {
//         for (int c = 0; c < cols; ++c) {
//             col_major[c * rows + r] = matrix[r * cols + c];
//         }
//     }
//
//     return col_major;
// }

// double* transpose_row_major(const double* matrix, int rows, int cols) {
//     double* transposed = new double[rows * cols];
//
//     for (int r = 0; r < rows; ++r) {
//         for (int c = 0; c < cols; ++c) {
//             transposed[c * rows + r] = matrix[r * cols + c];
//         }
//     }
//
//     return transposed;
// }

void test_mv_row_major() {
    int rows = 2;
    int cols = 3;

    double* matrix = new double[6]{
        1, 2, 3,
        4, 5, 6
    };

    double* vec = new double[3] {
        10,
        20,
        30
    };
    double* result = new double[2];
    double expected[2] {
        140,
        320
    };

    multiply_mv_row_major(matrix, rows, cols, vec, result);

    if (check_vector(result, expected, rows)) {
        cout << "test_mv_row_major: PASS" << endl;
    } else {
        cout << "test_mv_row_major: FAIL" << endl;
    }

    delete[] matrix;
    delete[] vec;
    delete[] result;
}

void test_mv_col_major() {
    int rows = 2;
    int cols = 3;

    // double* matrix_row_major = new double[6]{
    //     1, 2, 3,
    //     4, 5, 6
    // };

    double* matrix_col_major = new double[6] {
        1, 4,
        2, 5,
        3, 6
    };

    // double* matrix_col_major = row_major_to_col_major(matrix_row_major, rows, cols);
    double* vec = new double[3] {
        10,
        20,
        30
    };
    double* result = new double[2];
    double expected[2] {
        140,
        320
    };

    multiply_mv_col_major(matrix_col_major, rows, cols, vec, result);

    if (check_vector(result, expected, rows)) {
        cout << "test_mv_col_major: PASS" << endl;
    } else {
        cout << "test_mv_col_major: FAIL" << endl;
    }

    // delete[] matrix_row_major;
    delete[] matrix_col_major;
    delete[] vec;
    delete[] result;
}

void test_mm_naive() {
    int rowsA = 2;
    int colsA = 3;
    int rowsB = 3;
    int colsB = 4;

    double* A = new double[6]{
        1, 2, 3,
        4, 5, 6
    };

    double* B = new double[12]{
        7,  8,  9,  10,
        11, 12, 13, 14,
        15, 16, 17, 18
    };

    double* result = new double[8];

    double expected[8]{
        74, 80, 86, 92,
        173, 188, 203, 218
    };

    multiply_mm_naive(A, rowsA, colsA, B, rowsB, colsB, result);

    if (check_matrix(result, expected, rowsA, colsB)) {
        cout << "test_mm_naive: PASS" << endl;
    } else {
        cout << "test_mm_naive: FAIL" << endl;
    }

    delete[] A;
    delete[] B;
    delete[] result;
}

void test_mm_transposed_b() {
    int rowsA = 2;
    int colsA = 3;
    int rowsB = 3;
    int colsB = 4;

    double* A = new double[6]{
        1, 2, 3,
        4, 5, 6
    };

    // double* B = new double[12]{
    //     7,  8,  9,  10,
    //     11, 12, 13, 14,
    //     15, 16, 17, 18
    // };

    double* B_transposed = new double[12]{
        7, 11, 15,
        8, 12, 16,
        9, 13, 17,
        10, 14, 18
    };


    // double* B_transposed = transpose_row_major(B, rowsB, colsB);
    double* result = new double[8];

    double expected[8]{
        74, 80, 86, 92,
        173, 188, 203, 218
    };

    multiply_mm_transposed_b(A, rowsA, colsA, B_transposed, rowsB, colsB, result);

    if (check_matrix(result, expected, rowsA, colsB)) {
        cout << "test_mm_transposed_b: PASS" << endl;
    } else {
        cout << "test_mm_transposed_b: FAIL" << endl;
    }

    delete[] A;
    // delete[] B;
    delete[] B_transposed;
    delete[] result;
}



bool check_matrix_equal(const double* a, const double* b, int rows, int cols, double eps = 1e-9) {
    for (int i = 0; i < rows * cols; ++i) {
        if (!nearly_equal(a[i], b[i], eps)) {
            return false;
        }
    }
    return true;
}


double* transpose_row_major(const double* matrix, int rows, int cols) {
    double* transposed = new double[rows * cols];

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            transposed[c * rows + r] = matrix[r * cols + c];
        }
    }

    return transposed;
}


void test_mm_correctness() {
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

    double* B_transposed = transpose_row_major(B, rowsB, colsB);

    double* result_naive = new double[rowsA * colsB];
    double* result_transposed = new double[rowsA * colsB];

    double expected[8]{
        74, 80, 86, 92,
        173, 188, 203, 218
    };

    multiply_mm_naive(A, rowsA, colsA, B, rowsB, colsB, result_naive);
    multiply_mm_transposed_b(A, rowsA, colsA, B_transposed, rowsB, colsB, result_transposed);

    cout << "test_mm_naive vs expected: "
         << (check_matrix_equal(result_naive, expected, rowsA, colsB) ? "PASS" : "FAIL")
         << endl;

    cout << "test_mm_transposed_b vs expected: "
         << (check_matrix_equal(result_transposed, expected, rowsA, colsB) ? "PASS" : "FAIL")
         << endl;

    cout << "test_mm_naive vs mm_transposed_b: "
         << (check_matrix_equal(result_naive, result_transposed, rowsA, colsB) ? "PASS" : "FAIL")
         << endl;

    delete[] A;
    delete[] B;
    delete[] B_transposed;
    delete[] result_naive;
    delete[] result_transposed;
}