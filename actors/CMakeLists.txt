
add_executable(actors_caf_hello_world caf_hello_world.cpp)
target_link_libraries(actors_caf_hello_world PRIVATE CAF::io)
