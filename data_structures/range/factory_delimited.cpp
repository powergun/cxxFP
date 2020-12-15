//
// Created by weining on 11/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <utility>
#include <range/v3/all.hpp>
#include <iostream>

#include <ranges>

// FP in C++ P/151
// the "end" iterator is a special value, called sentinel;
// it gives you more freedom when implementing a test for whether you have
// reached the end of a range.

// a delimited range is one whose end you don't know in advance - but you
// have a predicate function that can tell you when you have reached the
// end.
// examples are null-terminated strings

// FP in C++ P/151
// range-based for loops and sentinels
// the c++11/14 range based for loop requires both the begin and end to have
// the same type - they need to be iterators. The sentinel based ranges
// can not be used with the range based for loop.
// C++17 removed this requirement.
// you can now have different types for the begin and end, which effectively
// means the end can be a sentinel.

TEST_CASE( "warm up: tuple decomposition in range-based for-loop (requires c++17)" )
{
    std::vector< std::tuple< int, int, int > > xs{ { 1, 2, 3 }, { 10, 20, 30 } };
    int sum = 0;
    for ( const auto &[ x, y, z ] : xs )
    {
        sum += y;
    }
    CHECK_EQ( sum, 22 );
}

TEST_CASE( "warm-up 2: tuple decomposition in STL algorithms (requires c++17)" )
{
    std::vector< std::tuple< int, int > > ns{ { 1, 2 }, { 3, 4 } };
    auto o = std::accumulate(
        ns.cbegin(), ns.cend(), 0, []( const auto &acc, const auto &tu ) {
            const auto &[ _, b ] = tu;
            return acc + b;
        } );
    CHECK_EQ( o, 6 );
}

TEST_CASE( "infinite range and view-zip" )
{
    // source:
    // https://ericniebler.github.io/range-v3/index.html#autotoc_md8
    // (search for zip under `views`)
    // NOTE:
    // views::ints(init, ranges::unreachable) produces a monotonic infinite range-view,
    // starting at init; views::ints(first, last) produces a closed range-view [first,
    // last)

    using namespace ranges;
    std::vector< int > xs{ 0, 1, 2, 3 };
    auto ns = views::zip( xs, views::ints( -100, unreachable ) )
              | views::transform( []( const auto &tu ) {
                    const auto &[ _, b ] = tu;
                    return b;
                } )
              | views::take( 2 ) | to< std::vector< int > >();
    CHECK_EQ( ns, std::vector< int >{ -100, -99 } );
    {
        // c++20 ranges api
        // views::zip was not selected by the standard, therefore I have to use a
        // workaround to iterate over two ranges (internal mutability)
        auto v1 = std::ranges::iota_view{ -100, std::numeric_limits< long long >::max() }
                  | std::views::transform( [ idx = 0 ]( const auto &x ) mutable {
                        return std::make_pair( idx++, x );
                    } )
                  | std::views::take( 2 );
        auto xs = std::vector( v1.begin(), v1.end() );
        CHECK_EQ( xs[ 0 ].second, -100 );
    }
}

TEST_CASE( "range-based for loop and range-view (updated with c++20 syntax)" )
{
    using namespace ranges;
    /**
     * Python:
     * for i in range(1, 10): ...
     * */
    for ( const auto &x : views::ints( 1, 10 ) )
    {
        // do stuffs...
    }
    {
        // c++20 ranges api
        for ( const std::weakly_incrementable auto &x : std::ranges::iota_view{ 0, 3 } )
        {
            // do stuffs
        }
    }

    // some important data to be processed in an array-like fashion
    /**
     * Python:
     * for idx, x in enumerate(xs): ...
     * */
    std::vector< std::string > xs{ "a", "b", "c" };
    for ( const auto &[ idx, x ] : views::zip( views::ints( 0, unreachable ), xs ) )
    {
        std::cout << idx << x << ' ';
    }
    std::cout << '\n';

    {
        // c++20 ranges api
        std::ranges::for_each( std::ranges::iota_view{ 9, 12 },
                               [ idx = 0 ]( const auto &x ) mutable {
                                   // do stuffs with idx and x
                                   idx++;
                               } );

        // or use the c++20 new feature: initialize an auxiliary value in the range-
        // based for-loop
        for ( int idx = 0, sentinel = 12;
              const std::weakly_incrementable auto &x : std::ranges::iota_view{ 9, 12 } )
        {
            // do stuffs with idx and x
            // idx could even be an iterator to another collection.
            if ( idx >= sentinel )
            {
                break;
            }
            idx++;
        }
    }
}
