//
// Created by Moxiao Li on 4/4/26.
//
# include "../includes/baseline.h"

#include <iostream>
#include <ostream>

using namespace std;


void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    // check for null pointer
    if (matrix == nullptr || vector == nullptr || result == nullptr) {
        cout << "Null pointer input in multiply_mv_row_major." << endl;
        return;
    }
    // check for dimensions
    if (rows <= 0 || cols <= 0) {
        cout << "Invalid dimensions in multiply_mv_row_major." << endl;
        return;
    }

    for (int r = 0; r < rows; ++r) {
        result[r] = 0;
        for (int c = 0; c < cols; ++c) {
            result[r] += matrix[r * cols + c] * vector[c];
        }
    }
}


void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    if (matrix == nullptr || vector == nullptr || result == nullptr) {
        cout << "Null pointer input in multiply_mv_col_major." << endl;
        return;
    }
    if (rows <= 0 || cols <= 0) {
        cout << "Invalid dimensions in multiply_mv_col_major." << endl;
        return;
    }

    for (int r = 0; r < rows; ++r) {
        result[r] = 0.0;
    }


    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            result[r] += matrix[r + c*rows] * vector[c];
        }
    }
}


void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result) {
    if (matrixA == nullptr || matrixB == nullptr || result == nullptr) {
        cout << "Null pointer input in multiply_mm_naive." << endl;
        return;
    }
    if (rowsA <= 0 || colsA <= 0 || rowsB <= 0 || colsB <= 0) {
        cout << "Invalid dimensions in multiply_mm_naive." << endl;
        return;
    }
    if (colsA != rowsB) {
        cout << "Number of columns of A does not equal number of rows of B." << endl;
        return;
    }

    for (int r_a = 0; r_a < rowsA; ++r_a) {
        for (int c_b = 0; c_b < colsB; ++c_b) {
            result[r_a*colsB + c_b] = 0;
            for (int r_b = 0; r_b < rowsB; ++r_b) {
                result[r_a*colsB + c_b] += matrixA[r_a*colsA + r_b] * matrixB[r_b*colsB + c_b];
            }
        }
    }
}


void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {
    if (matrixA == nullptr || matrixB_transposed == nullptr || result == nullptr) {
        cout << "Null pointer input in multiply_mm_naive." << endl;
        return;
    }
    if (rowsA <= 0 || colsA <= 0 || rowsB <= 0 || colsB <= 0) {
        cout << "Invalid dimensions in multiply_mm_naive." << endl;
        return;
    }
    if (colsA != rowsB) {
        cout << "Number of columns of A does not equal number of rows of B." << endl;
        return;
    }
    for (int r_a = 0; r_a < rowsA; ++r_a) {
        for (int c_b = 0; c_b < colsB; ++c_b) {
            result[r_a*colsB + c_b] = 0;
            for (int r_b = 0; r_b < rowsB; ++r_b) {
                result[r_a*colsB + c_b] += matrixA[r_a*colsA + r_b]* matrixB_transposed[c_b*rowsB + r_b];
            }
        }
    }
}
