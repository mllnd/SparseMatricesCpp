cmake_minimum_required(VERSION 3.12)
project(SparseMatricesClass)

set(CMAKE_CXX_STANDARD 14)

add_executable(SparseMatricesClass main.cpp SparseMatrix.cpp SparseMatrix.h Cell.cpp Cell.h)