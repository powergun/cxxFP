add_executable(sum_type_variant variant.cpp)
target_link_libraries(sum_type_variant PRIVATE doctest)
add_test(NAME "sum-type::variant" COMMAND sum_type_variant)

add_executable(sum_type_variant_pattern_matching variant_pattern_matching.cpp)
target_link_libraries(sum_type_variant_pattern_matching PRIVATE doctest)
add_test(NAME "sum-type::variant_pattern_matching" COMMAND sum_type_variant_pattern_matching)