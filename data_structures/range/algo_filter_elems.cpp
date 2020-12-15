//
// Created by weining on 19/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

#include <array>
#include <sstream>
#include <iostream>

#include <range/v3/all.hpp>
#include <ranges>
#include <algorithm>

TEST_CASE( "filter range using boost range v3 and cxx20" )
{
    std::array< int, 6 > arr{ { 1, 2, 3, 4, 5, 60 } };
    {
        std::ostringstream oss;
        boost::copy( boost::adaptors::filter( arr,
                                              []( auto &em ) {
                                                  // emit some side effect
                                                  std::cout
                                                      << "called inside filter: " << em
                                                      << '\n';
                                                  return em > 10;
                                              } ),
                     std::ostream_iterator< int >{ oss, "" } );
        CHECK_EQ( "60", oss.str() );
    }
    {
        // range-v3
        std::ostringstream oss;
        ranges::copy(
            arr | ranges::views::filter( []( const auto &x ) { return x > 10; } ),
            std::ostream_iterator< int >{ oss, "" } );
        CHECK_EQ( "60", oss.str() );
    }
    {
        // c++20 ranges api
        std::ostringstream oss;
        std::ranges::copy(
            arr | std::views::filter( []( const auto &x ) { return x > 10; } ),
            std::ostream_iterator< int >{ oss, "" } );
        CHECK_EQ( "60", oss.str() );
    }
}