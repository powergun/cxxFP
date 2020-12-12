add_executable(decompose_tuple_unpack tuple_unpack.cpp)
target_link_libraries(decompose_tuple_unpack PRIVATE doctest)
add_test(NAME "semantics::decompose::tuple-unpack" COMMAND decompose_tuple_unpack)

add_executable(decompose_array_unpack array_unpack.cpp)
target_link_libraries(decompose_array_unpack PRIVATE doctest)
add_test(NAME "semantics::decompose::array-unpack" COMMAND decompose_array_unpack)

add_executable(decompose_tuple_apply tuple_apply.cpp)
target_link_libraries(decompose_tuple_apply PRIVATE doctest)
add_test(NAME "semantics::decompose::tuple_apply" COMMAND decompose_tuple_apply)

