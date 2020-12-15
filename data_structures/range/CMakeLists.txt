
#######################################################
# producing ranges; factory

add_executable(range_factory_iota factory_iota.cpp)
target_link_libraries(range_factory_iota PRIVATE doctest ${Boost_LIBRARIES} range-v3)
target_include_directories(range_factory_iota PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range::factory::iota" COMMAND range_factory_iota)

add_executable(range_factory_istream_range factory_istream_range.cpp)
target_link_libraries(range_factory_istream_range PRIVATE doctest ${Boost_LIBRARIES} range-v3)
target_include_directories(range_factory_istream_range PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range::factory::istream_range" COMMAND range_factory_istream_range)

#######################################################
# range-based algorithms

add_executable(range_algorithm_count_elems algo_count_elems.cpp)
target_link_libraries(range_algorithm_count_elems PRIVATE doctest ${Boost_LIBRARIES} range-v3)
target_include_directories(range_algorithm_count_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range::algorithm::count-elems" COMMAND range_algorithm_count_elems)

add_executable(range_algorithm_copy_elems algo_copy_elems.cpp)
target_link_libraries(range_algorithm_copy_elems PRIVATE doctest ${Boost_LIBRARIES} range-v3)
target_include_directories(range_algorithm_copy_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range::algorithm::copy-elems" COMMAND range_algorithm_copy_elems)

add_executable(range_algorithm_schwartzian_transform algo_schwartzian_transform.cpp)
target_link_libraries(range_algorithm_schwartzian_transform PRIVATE doctest range-v3)
add_test(NAME "range::algorithm::perl_schwartzian_transform" COMMAND range_algorithm_schwartzian_transform)






add_executable(range_adapter_filter adapter_filter.cpp)
target_link_libraries(range_adapter_filter PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(range_adapter_filter PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:adapter-filter" COMMAND range_adapter_filter)

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

add_executable(range_actions range_actions.cpp)
target_link_libraries(range_actions PRIVATE doctest range-v3)
add_test(NAME "range::actions" COMMAND range_actions)

add_executable(range_delimited range_delimited.cpp)
target_link_libraries(range_delimited PRIVATE doctest range-v3)
add_test(NAME "range::delimited_ranges" COMMAND range_delimited)

add_executable(range_word_frequency word_frequency.cpp)
target_link_libraries(range_word_frequency PRIVATE doctest range-v3)
add_test(NAME "range::word_frequency_views_actions" COMMAND range_word_frequency)
