
add_executable(range_count_elems count_elems.cpp)
target_link_libraries(range_count_elems PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_count_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:count-elems" COMMAND range_count_elems)

add_executable(range_copy_elems copy_elems.cpp)
target_link_libraries(range_copy_elems PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_copy_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:copy-elems" COMMAND range_copy_elems)

add_executable(range_adapter_filter adapter_filter.cpp)
target_link_libraries(range_adapter_filter PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_adapter_filter PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:adapter-filter" COMMAND range_adapter_filter)

add_executable(range_irange irange.cpp)
target_link_libraries(range_irange PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_irange PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:irange-python-range" COMMAND range_irange)

add_executable(range_irange_stdin irange_stdin.cpp)
target_link_libraries(range_irange_stdin PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_irange_stdin PRIVATE ${Boost_INCLUDE_DIRS})

add_executable(range_range_v3 rangev3.cpp)
target_link_libraries(range_range_v3 PRIVATE doctest range-v3)
add_test(NAME "range::range-v3" COMMAND range_range_v3)

add_executable(range_range_v3_piping rangev3_piping.cpp)
target_link_libraries(range_range_v3_piping PRIVATE doctest range-v3)
add_test(NAME "range::range-v3-piping" COMMAND range_range_v3_piping)

add_executable(range_range_v3_perf rangev3_perf.cpp)
target_link_libraries(range_range_v3_perf PRIVATE doctest range-v3)
add_test(NAME "range::range-v3-performance" COMMAND range_range_v3_perf)

add_executable(range_map_as_pipe map_as_pipe.cpp)
target_link_libraries(range_map_as_pipe PRIVATE doctest range-v3)
add_test(NAME "range::map-as-pipe" COMMAND range_map_as_pipe)

add_executable(range_map_filter_composing map_filter_composing.cpp)
target_link_libraries(range_map_filter_composing PRIVATE doctest range-v3)
add_test(NAME "range::map-filter-composing" COMMAND range_map_filter_composing)