
add_executable(lazy_eval_value lazy_value.cpp)
target_link_libraries(lazy_eval_value PRIVATE doctest)
add_test(NAME "lazy-evaluation::lazy_value" COMMAND lazy_eval_value)