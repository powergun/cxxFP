//
// Created by weining on 19/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

#include <vector>
#include <sstream>

#include <range/v3/all.hpp>
#include <ranges>
#include <algorithm>

TEST_CASE( "test: copy elements using range libraries" )
{
    {
        using namespace std;

        ostringstream oss;
        boost::copy( vector< int >( 9 ), ostream_iterator< int >{ oss, "," } );
        CHECK_EQ( "0,0,0,0,0,0,0,0,0,", oss.str() );

        vector< int > v{ 1, 1, 2, 3, 4, 5 };
        boost::random_shuffle( v );
        boost::copy( v, ostream_iterator< int >{ cout, " " } );

        // no bound check! if n > size, it will sigfault
        boost::copy_n( v, 2, ostream_iterator< int >{ cout, " " } );
    }
    {
        // range-v3
        // repeat_view (infinite stream of the same value); iota_view (finite/infinite
        // stream of a monotonically increasing sequence)
        std::ostringstream oss;
        ranges::copy( ranges::repeat_view{ 0 } | ranges::views::take( 9 ),
                      std::ostream_iterator< int >{ oss, "," } );
        CHECK_EQ( "0,0,0,0,0,0,0,0,0,", oss.str() );
    }
    {
        // c++20 ranges api; note it misses the repeat_view() helper, so I have to create
        // a temporary vector rvalue
        std::ostringstream oss;
        std::ranges::copy( std::vector< int >( 9 ),
                           std::ostream_iterator< int >{ oss, "," } );
        CHECK_EQ( "0,0,0,0,0,0,0,0,0,", oss.str() );
    }
}
