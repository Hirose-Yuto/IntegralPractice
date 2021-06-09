cmake_minimum_required(VERSION 3.19)
project(IntegrationGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(generator generator/main.cpp generator/generator.cpp generator/generator.h
        generator/polynomial.cpp generator/polynomial.h generator/fraction.cpp generator/fraction.h)

