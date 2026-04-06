#include "../includes/baseline.h"
#include "../includes/baseline_tests.h"
#include "../includes/benchmark.h"
#include "../includes/optimized.h"
#include "../includes/profile_mm_naive.h"
#include "../includes/profile_mm_transposed.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    cout << "Running Part 1 tests..." << endl;

    test_mv_row_major();
    test_mv_col_major();
    test_mm_naive();
    test_mm_transposed_b();
    test_mm_correctness();
    test_mm_blocked();

    int runs = 100;

    cout << "=== Matrix-Vector Benchmarks ===" << endl;
    benchmark_mv_case(128, runs);
    benchmark_mv_case(256, runs);
    benchmark_mv_case(512, runs);

    cout << "=== Matrix-Matrix Benchmarks ===" << endl;
    benchmark_mm_case(64, runs);
    benchmark_mm_case(128, runs);
    benchmark_mm_case(256, runs);

    // 2**(24)
    run_locality_benchmarks(1 << 24, runs);

    cout << "=== Memory Alignment Benchmarks ===" << endl;
    benchmark_mv_alignment_case(256, runs);
    benchmark_mv_alignment_case(512, runs);

    benchmark_mm_alignment_case(128, runs);
    benchmark_mm_alignment_case(256, runs);
    run_profile_mm_naive();
    run_profile_mm_transposed();
    run_optimized_black();



    return 0;
}