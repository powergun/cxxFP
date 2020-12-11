cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc-9)
set(CMAKE_CXX_COMPILER g++-9)

project(cxxFP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dependencies:

add_subdirectory(vendor/doctest)
enable_testing()

set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)
find_package(Boost 1.72.0 REQUIRED)

add_library(neither INTERFACE)
target_include_directories(neither INTERFACE vendor/neither-0.5.0/neither)
add_subdirectory(vendor/range-v3)

# sub projects:

add_subdirectory(semantics)
add_subdirectory(types)
add_subdirectory(functor)
add_subdirectory(lazy_evaluation)
add_subdirectory(data_structures)
