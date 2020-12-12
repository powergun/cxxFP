add_subdirectory(higher_order)
add_subdirectory(decompose)
add_subdirectory(recursion)

add_executable(composition_compose compose.cpp)
target_link_libraries(composition_compose doctest)
add_test(NAME "cxxFP::composition::compose" COMMAND composition_compose)

add_executable(composition_partial partial_application.cpp)
target_link_libraries(composition_partial doctest)
add_test(NAME "cxxFP::composition::partial" COMMAND composition_partial)

add_executable(func_application_invoke invoke.cpp)
target_link_libraries(func_application_invoke PRIVATE doctest)
add_test(NAME "func-application::invoke" COMMAND func_application_invoke)

