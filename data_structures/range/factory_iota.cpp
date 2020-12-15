#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/factory_iota.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>

#include <map>
#include <ranges>
#include <numeric>
#include <utility>
#include <algorithm>

#include <range/v3/all.hpp>

// these examples show how to construct an iota (incrementing range) and make use of it;
// note that c++20 relax the restriction on range-based for-loop so that I can directly
// pass a iota_view to it.

int fib( int n )
{
    if ( n == 1 or n == 0 )
        return 1;
    return fib( n - 1 ) + fib( n - 2 );
}

TEST_CASE( "irange: python range()" )
{
    // like python's, irange is exclusive, [0 , 10)
    CHECK_EQ( 45, boost::accumulate( boost::irange( 0, 10 ), 0, std::plus< int >{} ) );

    // range-v3
    CHECK_EQ( 45, ranges::accumulate( ranges::iota_view{ 0, 10 }, 0 ) );

    {
        // c++ ranges api - it does not have the accumulate() function
        // meaning that it is broken
        auto _ = std::ranges::iota_view{ 0, 10 };
    }
}

TEST_CASE( "irange: generator" )
{
    {
        using namespace boost;

        std::map< int, int > m;
        for_each( irange( 0, 10 ), [ &m ]( auto n ) { m.insert( { n, fib( n ) } ); } );
        CHECK_EQ( 55, max_element( m )->second );
        CHECK_EQ( min_element( m )->second, m[ 1 ] );
        CHECK_EQ( m[ 2 ], 2 );
    }
    {
        // range-v3; also use c++20 algorithm::ranges
        // see this page: https://en.cppreference.com/w/cpp/algorithm/ranges/copy
        auto m2 = ranges::iota_view{ 0, 10 }
                  // [T] -> [Pair<T, T>]
                  // note that Pair's ctor automatically deduce T from its arguments
                  | ranges::views::transform( []( const auto &x ) {
                        return std::pair{ x, fib( x ) };
                    } )
                  // [Pair<T, T>] -> Map<T, T>
                  | ranges::to< std::map< int, int > >();
        CHECK_EQ( 55, std::ranges::max_element( m2 )->second );
        CHECK_EQ( std::ranges::min_element( m2 )->second, m2[ 1 ] );
        CHECK_EQ( m2[ 2 ], 2 );
    }
    {
        // c++20 ranges api
        // it does not provide the to<> function template
        auto v =
            std::ranges::iota_view{ 0, 10 } | std::views::transform( []( const auto &x ) {
                return std::pair{ x, fib( x ) };
            } );
    }
}

TEST_CASE( "irange: iteration" )
{
    {
        using namespace boost;
        int state = 0;
        for_each( irange( 1, 5 ), [ &state ]( const auto &idx ) {
            state += 1;  // do index-based things
        } );
        CHECK_EQ( state, 4 );
    }
    {
        // range-v3
        int state = 0;
        ranges::for_each( ranges::iota_view{ 1, 5 },
                          [ &state ]( const auto &x ) { state += 1; } );
        CHECK_EQ( state, 4 );
    }
    {
        // c++20 ranges api
        int state = 0;
        for( std::weakly_incrementable auto x : std::ranges::iota_view{ 1, 5 }) {
            state += 1;
        }
        CHECK_EQ( state, 4 );
    }
}
