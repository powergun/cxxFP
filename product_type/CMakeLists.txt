
add_executable(product_type_tuple tuple.cpp)
target_link_libraries(product_type_tuple PRIVATE doctest)
add_test(NAME "product-type::tuple" COMMAND product_type_tuple)

add_executable(product_type_tuple_apply tuple_apply.cpp)
target_link_libraries(product_type_tuple_apply PRIVATE doctest)
add_test(NAME "product-type::tuple-apply" COMMAND product_type_tuple_apply)