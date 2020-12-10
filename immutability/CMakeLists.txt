
add_executable(immut_builder_pattern builder_pattern.cpp)
target_link_libraries(immut_builder_pattern PRIVATE doctest)
add_test(NAME "immutability::builder_pattern" COMMAND immut_builder_pattern)