cmake_minimum_required(VERSION 3.10)
project(cxxFP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE doctest)

add_executable(higher_order_sort higher_order/sort.cpp)
target_link_libraries(higher_order_sort doctest)
add_test(NAME "cxxFP::higher_order::sort" COMMAND higher_order_sort)

add_executable(higher_order_copy higher_order/copy.cpp)
target_link_libraries(higher_order_copy doctest)
add_test(NAME "cxxFP::higher_order::copy" COMMAND higher_order_copy)

add_executable(higher_order_reduce higher_order/reduce.cpp)
target_link_libraries(higher_order_reduce doctest)
add_test(NAME "cxxFP::higher_order::reduce" COMMAND higher_order_reduce)

add_executable(composition_compose composition/compose.cpp)
target_link_libraries(composition_compose doctest)
add_test(NAME "cxxFP::composition::compose" COMMAND composition_compose)

add_executable(composition_partial composition/partial.cc)
target_link_libraries(composition_partial doctest)
add_test(NAME "cxxFP::composition::partial" COMMAND composition_partial)