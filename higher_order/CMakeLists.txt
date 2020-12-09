add_executable(higher_order_sort sort.cpp)
target_link_libraries(higher_order_sort doctest)
add_test(NAME "cxxFP::higher_order::sort" COMMAND higher_order_sort)

add_executable(higher_order_copy copy.cpp)
target_link_libraries(higher_order_copy doctest)
add_test(NAME "cxxFP::higher_order::copy" COMMAND higher_order_copy)

add_executable(higher_order_reduce reduce.cpp)
target_link_libraries(higher_order_reduce doctest)
add_test(NAME "cxxFP::higher_order::reduce" COMMAND higher_order_reduce)

add_executable(higher_order_map map.cpp)
target_link_libraries(higher_order_map doctest)
add_test(NAME "cxxFP::higher_order::map" COMMAND higher_order_map)

add_executable(higher_order_function_as_arg function_as_arguments.cpp)
target_link_libraries(higher_order_function_as_arg doctest)
add_test(NAME "cxxFP::higher_order::function_as_argument" COMMAND higher_order_function_as_arg)

add_executable(higher_order_lambda_member_variables lambda_member_variables.cpp)
target_link_libraries(higher_order_lambda_member_variables doctest range-v3)
add_test(NAME "cxxFP::higher_order::lambda_member_variables" COMMAND higher_order_lambda_member_variables)
