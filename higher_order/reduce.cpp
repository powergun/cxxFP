#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <vector>
#include <numeric>

TEST_CASE( "reduce: sum" )
{
    std::vector< int > elems{ 1, 2, 3, 4, 5 };
    CHECK( 15 == std::accumulate( elems.cbegin(), elems.cend(), 0 ) );
}

TEST_CASE( "reduce: conditional sum" )
{
    std::vector< int > elems{ 1, 2, 3, 4, 5 };
    // NOTE:
    // accumulate is NOT foldr as it does not use recursion
    // accumulate is an iterative approach, with a function that
    // happens to have a similar type signature to foldr
    auto result =
        std::accumulate( elems.cbegin(), elems.cend(), 0, []( const auto &acc, const auto &elem ) {
            // this shows the order of evaluation is first to last
            // std::cout << acc << ", " << elem << std::endl;
            return elem % 2 == 0 ? acc + elem : acc;
        } );
    CHECK( 6 == result );
}

// apply the predicate f to all the elements and returns the logical AND
// of these results
TEST_CASE( "reduce: all_of" )
{
    std::vector< int > elems{ 1, 2, 3, 4, 5 };
    auto r1 = std::all_of( elems.cbegin(), elems.cend(), []( auto elem ) { return elem > 0; } );
    CHECK( r1 );

    std::string line{ "XXXX" };
    auto r2 = std::all_of( line.cbegin(), line.cend(), []( auto ch ) { return ch == 'X'; } );
    CHECK( r2 );
}

// none_of works in the opposite way: if for each elem, f(elem) is False, then the result is False
// it can be useful when testing if none of the elements are in some kind of (invalid) state
