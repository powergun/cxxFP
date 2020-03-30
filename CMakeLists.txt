cmake_minimum_required(VERSION 3.10)
project(cxxFP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE doctest)

add_subdirectory(higher_order)
add_subdirectory(composition)
add_subdirectory(type_driven)
