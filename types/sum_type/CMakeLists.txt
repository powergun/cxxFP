add_executable(sum_type_variant variant.cpp)
target_link_libraries(sum_type_variant PRIVATE doctest)
add_test(NAME "sum-type::variant" COMMAND sum_type_variant)