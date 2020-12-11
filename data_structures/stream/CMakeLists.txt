
add_executable(stream_split_to_subs split_stream.cpp)
target_link_libraries(stream_split_to_subs PRIVATE doctest)
add_test(NAME "stream::split-to-substreams" COMMAND stream_split_to_subs)

add_executable(stream_infinite infinite_stream.cpp)
target_link_libraries(stream_infinite PRIVATE doctest)
target_include_directories(stream_infinite PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "stream::infinite" COMMAND stream_infinite)


