//
// Created by Moxiao Li on 4/5/26.
//

#ifndef ADVANCED_COMPUTING_FOR_FINANCE_HPLA_PART1_H
#define ADVANCED_COMPUTING_FOR_FINANCE_HPLA_PART1_H


bool nearly_equal(double a, double b, double eps = 1e-9);

bool check_vector(const double* actual, const double* expected, int size);

bool check_matrix(const double* actual, const double* expected, int rows, int cols);

void test_mv_row_major();

void test_mv_col_major();

void test_mm_naive();

void test_mm_transposed_b();

void test_mm_correctness();

double* transpose_row_major(const double*, int, int);


#endif //ADVANCED_COMPUTING_FOR_FINANCE_HPLA_PART1_H