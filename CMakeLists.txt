cmake_minimum_required(VERSION 3.10)
project(cxxFP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/doctest)
enable_testing()

set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)
find_package(Boost 1.72.0 REQUIRED)

add_library(neither INTERFACE)
target_include_directories(neither INTERFACE vendor/neither-0.5.0/neither)

add_subdirectory(vendor/range-v3)

add_subdirectory(higher_order)
add_subdirectory(composition)
add_subdirectory(maybe)
add_subdirectory(range)
add_subdirectory(either)
add_subdirectory(pattern_matching)
add_subdirectory(sum_type)
add_subdirectory(lambda)
add_subdirectory(func_application)
