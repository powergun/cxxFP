
add_executable(actors_caf_hello_world caf_hello_world.cpp)
target_link_libraries(actors_caf_hello_world PRIVATE CAF::io)

add_executable(actors_simple simple_actor.cpp)
target_link_libraries(actors_simple PRIVATE doctest)
add_test(NAME "actors::simple" COMMAND actors_simple)