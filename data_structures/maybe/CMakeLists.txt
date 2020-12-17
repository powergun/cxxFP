add_executable(maybe_optional optional.cpp)
target_link_libraries(maybe_optional doctest)
add_test(NAME "maybe::optional" COMMAND maybe_optional)

add_executable(maybe_any any.cpp)
target_link_libraries(maybe_any doctest)
add_test(NAME "maybe::any" COMMAND maybe_any)

add_executable(simple_maybe_fmap simple_maybe_fmap.cpp)
target_link_libraries(simple_maybe_fmap doctest)
add_test(NAME "maybe::fmap" COMMAND simple_maybe_fmap)

add_executable(maybe_lazy_resource optional_lazy_resource.cpp)
target_link_libraries(maybe_lazy_resource doctest)
add_test(NAME "maybe::optional_lazy_resource" COMMAND maybe_lazy_resource)