add_subdirectory(maybe)
add_subdirectory(range)
add_subdirectory(stream)

add_executable(either_exception_handling either_exception.cpp)
target_link_libraries(either_exception_handling PRIVATE doctest neither)
add_test(NAME "ds::either::exception-handling" COMMAND either_exception_handling)

add_executable(immut_builder_pattern builder_pattern.cpp)
target_link_libraries(immut_builder_pattern PRIVATE doctest)
add_test(NAME "immutability::builder_pattern" COMMAND immut_builder_pattern)