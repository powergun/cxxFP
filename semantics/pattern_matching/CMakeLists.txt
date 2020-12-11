add_executable(pattern_matching_tuple_unpack tuple_unpack.cpp)
target_link_libraries(pattern_matching_tuple_unpack PRIVATE doctest)
add_test(NAME "pattern-matching::tuple-unpack" COMMAND pattern_matching_tuple_unpack)

add_executable(pattern_matching_array_unpack array_unpack.cpp)
target_link_libraries(pattern_matching_array_unpack PRIVATE doctest)
add_test(NAME "pattern-matching::array-unpack" COMMAND pattern_matching_array_unpack)

add_executable(pattern_matching_tuple_apply tuple_apply.cpp)
target_link_libraries(pattern_matching_tuple_apply PRIVATE doctest)
add_test(NAME "pattern-matching::tuple_apply" COMMAND pattern_matching_tuple_apply)

