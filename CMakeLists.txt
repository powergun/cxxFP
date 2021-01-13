cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER gcc-10)
set(CMAKE_CXX_COMPILER g++-10)

project(cxxFP)

set(CMAKE_CXX_STANDARD 20)
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

set(CAF_ROOT ${PROJECT_SOURCE_DIR}/vendor/caf)
find_package(CAF REQUIRED)

# sub projects:

add_subdirectory(semantics)
add_subdirectory(types)
add_subdirectory(functor)
add_subdirectory(lazy_evaluation)
add_subdirectory(data_structures)
add_subdirectory(actors)
add_subdirectory(effects)