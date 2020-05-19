
add_executable(stream_split_to_subs split_to_subs.cpp)
target_link_libraries(stream_split_to_subs PRIVATE doctest)
add_test(NAME "stream::split-to-substreams" COMMAND stream_split_to_subs)

