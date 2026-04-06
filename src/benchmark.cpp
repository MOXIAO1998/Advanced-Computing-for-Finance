#include "../includes/baseline.h"
#include "../includes/baseline_tests.h"
#include "../includes/benchmark.h"
#include "../includes/aligned_memory.h"
#include "../includes/optimized.h"
#include<iostream>
#include <vector>
#include <chrono>

using namespace std;

using Clock = chrono::high_resolution_clock;

double g_sink = 0.0;


Stats compute_stats(const vector<double>& times) {
    double sum = 0.0;
    for (double t : times) {
        sum += t;
    }

    double mean = sum / static_cast<double>(times.size());

    double variance_sum = 0.0;
    for (double t : times) {
        double diff = t - mean;
        variance_sum += diff * diff;
    }

    double stddev = sqrt(variance_sum / static_cast<double>(times.size()));

    return {mean, stddev};
}

template <typename Func>
Stats benchmark(Func func, int runs, int warmups = 2) {
    for (int i = 0; i < warmups; ++i) {
        func();
    }

    vector<double> times;
    times.reserve(runs);

    for (int i = 0; i < runs; ++i) {
        auto start = Clock::now();
        func();
        auto end = Clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        times.push_back(elapsed.count());
    }

    return compute_stats(times);
}

void fill_array(double* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = (i % 97) * 0.01 + 1.0;
    }
}


double* row_major_to_col_major(const double* matrix, int rows, int cols) {
    double* col_major = new double[rows * cols];

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            col_major[c * rows + r] = matrix[r * cols + c];
        }
    }

    return col_major;
}

void benchmark_mv_case(int n, int runs) {
    double* matrix_row = new double[n * n];
    double* vector_x = new double[n];
    double* result = new double[n];

    fill_array(matrix_row, n * n);
    fill_array(vector_x, n);

    double* matrix_col = row_major_to_col_major(matrix_row, n, n);

    Stats row_stats = benchmark([&]() {
        multiply_mv_row_major(matrix_row, n, n, vector_x, result);
        g_sink += result[n - 1];
    }, runs);

    Stats col_stats = benchmark([&]() {
        multiply_mv_col_major(matrix_col, n, n, vector_x, result);
        g_sink += result[n - 1];
    }, runs);

    cout << "n = " << n << endl;
    cout << "  mv_row_major : mean = " << row_stats.mean_ms
         << " ms, stddev = " << row_stats.stddev_ms << " ms" << endl;
    cout << "  mv_col_major : mean = " << col_stats.mean_ms
         << " ms, stddev = " << col_stats.stddev_ms << " ms" << endl;
    cout << endl;

    delete[] matrix_row;
    delete[] matrix_col;
    delete[] vector_x;
    delete[] result;
}



void benchmark_mm_case(int n, int runs) {
    double* matrixA = new double[n * n];
    double* matrixB = new double[n * n];
    double* matrixB_transposed = nullptr;
    double* result = new double[n * n];

    fill_array(matrixA, n * n);
    fill_array(matrixB, n * n);

    matrixB_transposed = transpose_row_major(matrixB, n, n);

    Stats naive_stats = benchmark([&]() {
        multiply_mm_naive(matrixA, n, n, matrixB, n, n, result);
        g_sink += result[n * n - 1];
    }, runs);

    Stats transposed_stats = benchmark([&]() {
        multiply_mm_transposed_b(matrixA, n, n, matrixB_transposed, n, n, result);
        g_sink += result[n * n - 1];
    }, runs);

    Stats blocked_stats = benchmark([&]() {
        multiply_mm_blocked(matrixA, n, n, matrixB, n, n, result);
        g_sink += result[n * n - 1];
    }, runs);

    cout << "n = " << n << endl;
    cout << "  mm_naive         : mean = " << naive_stats.mean_ms
         << " ms, stddev = " << naive_stats.stddev_ms << " ms" << endl;
    cout << "  mm_transposed_b  : mean = " << transposed_stats.mean_ms
         << " ms, stddev = " << transposed_stats.stddev_ms << " ms" << endl;
    cout << "  mm_blocked       : mean = " << blocked_stats.mean_ms
         << " ms, stddev = " << blocked_stats.stddev_ms << " ms" << endl;
    cout << endl;

    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixB_transposed;
    delete[] result;
}

void benchmark_locality_case(int size, int stride, int total_accesses, int runs) {
    double* arr = new double[size];
    fill_array(arr, size);

    Stats stride_stats = benchmark([&]() {
        double local_sum = 0.0;
        int index = 0;

        for (int t = 0; t < total_accesses; ++t) {
            local_sum += arr[index];
            index += stride;
            if (index >= size) {
                index -= size;
            }
        }

        g_sink += local_sum;
    }, runs);

    cout << "  stride = " << stride
         << " : mean = " << stride_stats.mean_ms
         << " ms, stddev = " << stride_stats.stddev_ms << " ms" << endl;

    delete[] arr;
}

void run_locality_benchmarks(int size, int runs) {
    cout << "=== Stride / Cache Locality Benchmarks ===" << endl;
    cout << "array size = " << size << endl;

    int total_accesses = 1 << 24;//2**24

    benchmark_locality_case(size, 1, total_accesses, runs);
    benchmark_locality_case(size, 2, total_accesses, runs);
    benchmark_locality_case(size, 4, total_accesses, runs);
    benchmark_locality_case(size, 8, total_accesses, runs);
    benchmark_locality_case(size, 16, total_accesses, runs);
    benchmark_locality_case(size, 32, total_accesses, runs);
    benchmark_locality_case(size, 64, total_accesses, runs);

    cout << endl;
}
void benchmark_mv_alignment_case(int n, int runs) {
    double* matrix_unaligned = new double[n * n];
    double* vector_unaligned = new double[n];
    double* result_unaligned = new double[n];

    fill_array(matrix_unaligned, n * n);
    fill_array(vector_unaligned, n);

    Stats unaligned_stats = benchmark([&]() {
        multiply_mv_row_major(matrix_unaligned, n, n, vector_unaligned, result_unaligned);
        g_sink += result_unaligned[n - 1];
    }, runs);

    delete[] matrix_unaligned;
    delete[] vector_unaligned;
    delete[] result_unaligned;

    double* matrix_aligned = allocate_aligned_doubles(static_cast<size_t>(n) * n);
    double* vector_aligned = allocate_aligned_doubles(n);
    double* result_aligned = allocate_aligned_doubles(n);

    fill_array(matrix_aligned, n * n);
    fill_array(vector_aligned, n);

    Stats aligned_stats = benchmark([&]() {
        multiply_mv_row_major(matrix_aligned, n, n, vector_aligned, result_aligned);
        g_sink += result_aligned[n - 1];
    }, runs);

    cout << "n = " << n << endl;
    cout << "  mv_row_major unaligned : mean = " << unaligned_stats.mean_ms
         << " ms, stddev = " << unaligned_stats.stddev_ms << " ms" << endl;
    cout << "  mv_row_major aligned   : mean = " << aligned_stats.mean_ms
         << " ms, stddev = " << aligned_stats.stddev_ms << " ms" << endl;
    cout << endl;

    free_aligned(matrix_aligned);
    free_aligned(vector_aligned);
    free_aligned(result_aligned);
}

void benchmark_mm_alignment_case(int n, int runs) {
    double* A_unaligned = new double[n * n];
    double* B_unaligned = new double[n * n];
    double* C_unaligned = new double[n * n];

    fill_array(A_unaligned, n * n);
    fill_array(B_unaligned, n * n);

    Stats unaligned_stats = benchmark([&]() {
        multiply_mm_naive(A_unaligned, n, n, B_unaligned, n, n, C_unaligned);
        g_sink += C_unaligned[n * n - 1];
    }, runs);

    delete[] A_unaligned;
    delete[] B_unaligned;
    delete[] C_unaligned;

    double* A_aligned = allocate_aligned_doubles(static_cast<size_t>(n) * n);
    double* B_aligned = allocate_aligned_doubles(static_cast<size_t>(n) * n);
    double* C_aligned = allocate_aligned_doubles(static_cast<size_t>(n) * n);

    fill_array(A_aligned, n * n);
    fill_array(B_aligned, n * n);

    Stats aligned_stats = benchmark([&]() {
        multiply_mm_naive(A_aligned, n, n, B_aligned, n, n, C_aligned);
        g_sink += C_aligned[n * n - 1];
    }, runs);

    cout << "n = " << n << endl;
    cout << "  mm_naive unaligned : mean = " << unaligned_stats.mean_ms
         << " ms, stddev = " << unaligned_stats.stddev_ms << " ms" << endl;
    cout << "  mm_naive aligned   : mean = " << aligned_stats.mean_ms
         << " ms, stddev = " << aligned_stats.stddev_ms << " ms" << endl;
    cout << endl;

    free_aligned(A_aligned);
    free_aligned(B_aligned);
    free_aligned(C_aligned);
}