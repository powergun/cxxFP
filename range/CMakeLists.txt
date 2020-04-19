
add_executable(count_elems count_elems.cpp)
target_link_libraries(count_elems PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(count_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:count-elems" COMMAND count_elems)

add_executable(copy_elems copy_elems.cpp)
target_link_libraries(copy_elems PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(copy_elems PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:copy-elems" COMMAND copy_elems)

add_executable(adapter_filter adapter_filter.cpp)
target_link_libraries(adapter_filter PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(adapter_filter PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:adapter-filter" COMMAND adapter_filter)

add_executable(irange irange.cpp)
target_link_libraries(irange PRIVATE doctest ${Boost_LIBRARIES})
target_include_directories(irange PRIVATE ${Boost_INCLUDE_DIRS})
add_test(NAME "range:irange-python-range" COMMAND irange)

