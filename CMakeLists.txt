cmake_minimum_required(VERSION 4.1)
project(Advanced_Computing_for_Finance)

set(CMAKE_CXX_STANDARD 20)

add_executable(Advanced_Computing_for_Finance src/main.cpp
        includes/HPLA.h
        src/HPLA.cpp)
