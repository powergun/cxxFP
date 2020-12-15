
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

add_executable(range_algorithm_for_each algo_for_each.cpp)
target_link_libraries(range_algorithm_for_each PRIVATE doctest range-v3)
add_test(NAME "range::algorithm::for_each" COMMAND range_algorithm_for_each)

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
add_test(NAME "range::algorithm::the_missing_to_vector" COMMAND range_algorithm_to_vector)

#######################################################
# performance micro benchmark

add_executable(range_bench_simple_immutable perf_simple_immutable.cpp)
target_link_libraries(range_bench_simple_immutable PRIVATE doctest range-v3)
add_test(NAME "range::bench::simple_immutable" COMMAND range_bench_simple_immutable)

add_executable(range_bench_simple_sort perf_simple_sort.cpp)
target_link_libraries(range_bench_simple_sort PRIVATE doctest range-v3)
add_test(NAME "range::bench::simple_sort" COMMAND range_bench_simple_sort)

#######################################################
# range composition

add_executable(range_composition_map_filter_basic comp_map_filter_basic.cpp)
target_link_libraries(range_composition_map_filter_basic PRIVATE doctest range-v3)
add_test(NAME "range::composition::map_filter_basic" COMMAND range_composition_map_filter_basic)

add_executable(range_composition_map_filter comp_map_filter.cpp)
target_link_libraries(range_composition_map_filter PRIVATE doctest range-v3)
add_test(NAME "range::composition::map_filter" COMMAND range_composition_map_filter)

add_executable(range_composition_pipe comp_pipe.cpp)
target_link_libraries(range_composition_pipe PRIVATE doctest range-v3)
add_test(NAME "range::composition::pipe" COMMAND range_composition_pipe)
