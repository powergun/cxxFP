cmake_minimum_required(VERSION 3.8)
project(cxxFP)

add_library(libFP
    src/immutable.cc
    )
set_target_properties(libFP
    PROPERTIES
    CXX_STANDARD 17)

add_executable(test_immutable tests/test_immutable.cc)
set_target_properties(test_immutable
    PROPERTIES
    CXX_STANDARD 17)
target_include_directories(test_immutable PRIVATE src)
target_link_libraries(test_immutable libFP)

add_executable(main src/main.cc)
set_target_properties(main
    PROPERTIES
    CXX_STANDARD 17)
