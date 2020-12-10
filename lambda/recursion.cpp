//
// Created by weining on 13/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <functional>
#include <iostream>

// modern c++ programming cookbook L3176
// must capture the lambda function in order to recursively
// invoke it; note the use of std::function wrapper

TEST_CASE( "" )
{
    std::function< int( int ) > fib = [ &fib ]( int n ) {
        if ( n == 0 or n == 1 )
            return 1;
        return fib( n - 1 ) + fib( n - 2 );
    };
    using namespace std;
    cout << fib( 20 ) << endl;
}
