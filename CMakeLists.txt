cmake_minimum_required(VERSION 3.8)
project(cxxFP)

add_executable(main src/main.cc)
set_target_properties(main
    PROPERTIES
    CXX_STANDARD 17)
