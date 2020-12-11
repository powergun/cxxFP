add_executable(recur_tailrec tailrec.cpp)
target_link_libraries(recur_tailrec PRIVATE doctest)
add_test(NAME "recursion::tailrec" COMMAND recur_tailrec)

add_executable(recursive_lambda recursive_lambda.cpp)
target_link_libraries(recursive_lambda PRIVATE doctest)
add_test(NAME "recursion::recursive_lambda" COMMAND recursive_lambda)
