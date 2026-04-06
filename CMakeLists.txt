cmake_minimum_required(VERSION 4.1)
project(Advanced_Computing_for_Finance)

set(CMAKE_CXX_STANDARD 20)

add_executable(Advanced_Computing_for_Finance src/main.cpp
        includes/baseline.h
        src/baseline.cpp
        src/baseline_tests.cpp
        includes/baseline_tests.h
        includes/aligned_memory.h
        includes/optimized.h
        src/benchmark.cpp
        src/optimized.cpp
        includes/benchmark.h
        src/aligned_memory.cpp
        src/profile_mm_naive.cpp
        src/profile_mm_transposed.cpp
        includes/profile_mm_transposed.h
        includes/profile_mm_naive.h)
