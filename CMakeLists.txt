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

add_subdirectory(higher_order)
add_subdirectory(composition)
add_subdirectory(type_driven)
add_subdirectory(range)
