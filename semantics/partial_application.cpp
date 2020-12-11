#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <functional>

// create partial function by returning a lambda object:
// see cxxAlgorithms/iteration/zip_tuples.cpp
// which returns lambda function to achieve partial application.

template < typename A >
A add( const A &a, const A &b )
{
    return a + b;
}

TEST_CASE( "demo: partial application using bind" )
{
    CHECK_EQ( 2, add( 1, 1 ) );

    // hands on FP with C++ L1652
    // bind has higher compile time overhead than lambda
    auto increment = std::bind( add< int >, 1, std::placeholders::_1 );
    CHECK_EQ( 2, increment( 1 ) );
}