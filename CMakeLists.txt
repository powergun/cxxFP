cmake_minimum_required(VERSION 3.8)
project(cxxFP)

add_library(lib_immutable src/immutable.cc)
set_target_properties(lib_immutable
    PROPERTIES
    CXX_STANDARD 17)

add_executable(test_immutable tests/test_immutable.cc)
set_target_properties(test_immutable
    PROPERTIES
    CXX_STANDARD 17)
target_include_directories(test_immutable PRIVATE src)
target_link_libraries(test_immutable lib_immutable)

add_executable(main src/main.cc)
set_target_properties(main
    PROPERTIES
    CXX_STANDARD 17)
