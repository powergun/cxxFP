cmake_minimum_required(VERSION 3.10)
project(cxxFP)

# see:
# https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include(tinyCUnit/tinyCUnit.cmake)

# how to create a header only library
# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
add_library(utilities INTERFACE)
target_include_directories(utilities INTERFACE utilities/)


add_tinytest_executable(higher_order_sort
        higher_order/sort.cpp)
target_link_libraries(higher_order_sort utilities)
add_test(
        NAME "cxxFP::higher_order::sort"
        COMMAND higher_order_sort)


add_tinytest_executable(higher_order_copy
        higher_order/copy.cpp)
target_link_libraries(higher_order_copy utilities)
add_test(
        NAME "cxxFP::higher_order::copy"
        COMMAND higher_order_copy)


add_tinytest_executable(higher_order_reduce
        higher_order/reduce.cpp)
target_link_libraries(higher_order_reduce utilities)
add_test(
        NAME "cxxFP::higher_order::reduce"
        COMMAND higher_order_reduce)