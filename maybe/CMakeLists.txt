add_executable(maybe_optional optional.cpp)
target_link_libraries(maybe_optional doctest)
add_test(NAME "maybe::optional" COMMAND maybe_optional)