add_executable(maybe_optional optional.cpp)
target_link_libraries(maybe_optional doctest)
add_test(NAME "maybe::optional" COMMAND maybe_optional)

add_executable(maybe_any any.cpp)
target_link_libraries(maybe_any doctest)
add_test(NAME "maybe::any" COMMAND maybe_any)