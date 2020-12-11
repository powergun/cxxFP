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

TEST_CASE( "filter range using adapter" )
{
    using namespace std;

    ostringstream oss;
    array< int, 6 > arr{ { 1, 2, 3, 4, 5, 60 } };
    boost::copy( boost::adaptors::filter( arr,
                                          []( auto &em ) {
                                              // emit some side effect
                                              cout << "called inside filter: " << em << endl;
                                              return em > 10;
                                          } ),
                 ostream_iterator< int >{ oss, "" } );
    CHECK_EQ( "60", oss.str() );
}