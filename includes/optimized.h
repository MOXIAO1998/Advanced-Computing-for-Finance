//
// Created by Moxiao Li on 4/5/26.
//

#ifndef ADVANCED_COMPUTING_FOR_FINANCE_OPTIMIZED_H
#define ADVANCED_COMPUTING_FOR_FINANCE_OPTIMIZED_H

void multiply_mm_blocked(const double* matrixA, int rowsA, int colsA,
const double* matrixB, int rowsB, int colsB,
double* result);

void test_mm_blocked();

void run_optimized_black();

#endif //ADVANCED_COMPUTING_FOR_FINANCE_OPTIMIZED_H