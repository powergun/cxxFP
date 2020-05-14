
add_executable(func_application_invoke invoke.cpp)
target_link_libraries(func_application_invoke PRIVATE doctest)
add_test(NAME "func-application::invoke" COMMAND func_application_invoke)
