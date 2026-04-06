//
// Created by Moxiao Li on 4/4/26.
//

#ifndef ADVANCED_COMPUTING_FOR_FINANCE_HPLA_H
#define ADVANCED_COMPUTING_FOR_FINANCE_HPLA_H

void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result);


void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result);



void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result);


void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result);


#endif //ADVANCED_COMPUTING_FOR_FINANCE_HPLA_H