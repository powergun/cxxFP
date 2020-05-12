add_executable(lambda_recursion recursion.cpp)
target_link_libraries(lambda_recursion PRIVATE doctest)
add_test(NAME "lambda::recursion" COMMAND lambda_recursion)