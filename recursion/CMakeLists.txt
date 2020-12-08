add_executable(recur_tailrec tailrec.cpp)
target_link_libraries(recur_tailrec PRIVATE doctest)
add_test(NAME "recursion::tailrec" COMMAND recur_tailrec)
