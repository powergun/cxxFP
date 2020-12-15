
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

add_executable(range_factory_delimited_range factory_delimited.cpp)
target_link_libraries(range_factory_delimited_range PRIVATE doctest range-v3)
add_test(NAME "range::factory::delimited_ranges" COMMAND range_factory_delimited_range)

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

add_executable(range_algorithm_filter_elements algo_filter_elems.cpp)
target_link_libraries(range_algorithm_filter_elements PRIVATE doctest ${Boost_LIBRARIES} range-v3)
target_include_directories(range_algorithm_filter_elements PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range::algorithm::filter_elements" COMMAND range_algorithm_filter_elements)

add_executable(range_algorithm_schwartzian_transform algo_schwartzian_transform.cpp)
target_link_libraries(range_algorithm_schwartzian_transform PRIVATE doctest range-v3)
add_test(NAME "range::algorithm::perl_schwartzian_transform" COMMAND range_algorithm_schwartzian_transform)

add_executable(range_algorithm_word_frequency algo_word_frequency.cpp)
target_link_libraries(range_algorithm_word_frequency PRIVATE doctest range-v3)
add_test(NAME "range::algorithm::word_frequency_views_actions" COMMAND range_algorithm_word_frequency)

add_executable(range_algorithm_to_vector algo_cxx20_to_vector.cpp)
target_link_libraries(range_algorithm_to_vector PRIVATE doctest range-v3)
add_test(NAME "range::algorithm::(the missing)to_vector" COMMAND range_algorithm_to_vector)



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
