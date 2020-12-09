//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <boost/phoenix.hpp>

// FP in c++ P/66 mentions boost::phoenix library while explaining the generic lambdas;
// also at DA, I've heard of the author of this library;
// this example shows how to make use of it

TEST_CASE( "asd" )
{
    auto v = boost::phoenix::val( 1 );
}
