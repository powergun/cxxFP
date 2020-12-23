add_subdirectory(product_type)
add_subdirectory(sum_type)

add_executable(types_recursive recursive_type.cpp)
target_link_libraries(types_recursive PRIVATE doctest)
add_test(NAME "types::recursive_type" COMMAND types_recursive)