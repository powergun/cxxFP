//
// Created by weining on 19/4/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/istream_range.hpp>

#include <sstream>
#include <vector>

// source:
// https://theboostcpplibraries.com/boost.range-helper-classes-and-functions
TEST_CASE ("read numbers") {
    using namespace boost;

    std::vector<int> v;
    v.reserve(10);
    std::stringstream ss("123");
    iterator_range<std::istream_iterator<int>> ir =
        istream_range<int>(ss);
    boost::copy(ir, v.begin());

    boost::copy(v, std::ostream_iterator<int>{std::cout, "\n"});
}