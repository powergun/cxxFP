add_executable(composition_compose compose.cpp)
target_link_libraries(composition_compose doctest)
add_test(NAME "cxxFP::composition::compose" COMMAND composition_compose)

add_executable(composition_partial partial.cc)
target_link_libraries(composition_partial doctest)
add_test(NAME "cxxFP::composition::partial" COMMAND composition_partial)