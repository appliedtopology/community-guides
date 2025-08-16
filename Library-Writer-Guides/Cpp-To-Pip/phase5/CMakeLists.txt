cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(UnionFind VERSION 0.1)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

configure_file(union-find-config.h.in union-find-config.h)

pybind11_add_module(unionfind glue.cpp union-find.cpp)
install(TARGETS unionfind DESTINATION .)
target_include_directories(unionfind PUBLIC "${PROJECT_BINARY_DIR}")
