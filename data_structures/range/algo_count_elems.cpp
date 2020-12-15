#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <array>
#include <range/v3/all.hpp>
#include <algorithm>

// inspired by hands on functional programming with C++ L4189
// NOTE: boost provides its own range library
// source:
// https://theboostcpplibraries.com/boost.range-algorithms

TEST_CASE( "count occurrence of element " )
{
    std::array< int, 6 > a{ { 0, 1, 0, 1, 0, 1 } };
    {
        CHECK_EQ( 3, boost::count( a, 0 ) );
        CHECK_EQ( 1, boost::count( std::vector< int >{ 1, 2, 3 }, 1 ) );
        CHECK_EQ( 999, boost::count( std::vector< bool >( 999 ), false ) );
    }
    {
        // range-v3
        CHECK_EQ( 3, ranges::count( a, 0 ) );
        CHECK_EQ( 1, ranges::count( ranges::iota_view{ 1, 9 }, 1 ) );
        CHECK_EQ( 999, ranges::count( ranges::repeat_n_view( false, 999 ), false ) );
    }
    {
        // c++20 ranges api
        CHECK_EQ( 3, std::ranges::count( a, 0 ) );
        CHECK_EQ( 1, std::ranges::count( std::ranges::iota_view{ 0, 9 }, 1 ) );
        CHECK_EQ( 999,
                  std::ranges::count( std::ranges::iota_view{ 0, 999 }
                                          | std::views::transform(
                                              []( const auto &x ) { return false; } ),
                                      false ) );
    }
}
