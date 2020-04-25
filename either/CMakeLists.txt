
add_executable(either_exception_handling exception.cpp)
target_link_libraries(either_exception_handling PRIVATE doctest neither)
add_test(NAME "either::exception-handling" COMMAND either_exception_handling)
