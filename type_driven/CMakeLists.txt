add_executable(type_driven_optional optional.cpp)
target_link_libraries(type_driven_optional doctest)
add_test(NAME "cxxFP::type_driven::optional" COMMAND type_driven_optional)