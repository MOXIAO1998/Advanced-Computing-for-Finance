//
// Created by Moxiao Li on 4/5/26.
//

#ifndef ADVANCED_COMPUTING_FOR_FINANCE_BENCHMARK_H
#define ADVANCED_COMPUTING_FOR_FINANCE_BENCHMARK_H

#include <vector>

extern double g_sink;

struct Stats {
    double mean_ms;
    double stddev_ms;

};

Stats compute_stats(const std::vector<double>& times);

void fill_array(double* arr, int size);

double* row_major_to_col_major(const double* matrix, int rows, int cols);

void benchmark_mv_case(int n, int runs);


void benchmark_mm_case(int n, int runs);

void benchmark_locality_case(int size, int stride, int total_accesses, int runs);
void run_locality_benchmarks(int size, int runs);


void benchmark_mv_alignment_case(int n, int runs);
void benchmark_mm_alignment_case(int n, int runs);
#endif //ADVANCED_COMPUTING_FOR_FINANCE_BENCHMARK_H