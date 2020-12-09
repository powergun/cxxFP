//
// Created by weining on 19/4/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

#include <vector>
#include <sstream>

TEST_CASE( "copy elements using range" )
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
