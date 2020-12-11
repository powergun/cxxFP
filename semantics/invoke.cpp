//
// Created by weining on 14/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <functional>

// modern c++ programming cookbook L3664
// std::invoke() function is a variadic func template that takes the callable
// object as the first argument and a variable list of arguments that are passed
// to the call

// free function
int add( int a, int b )
{
    return a + b;
}

struct Foo
{
    int add( int a, int b )
    {
        return a + b;
    }

    static int s_add( int a, int b )
    {
        return a + b;
    }
};

TEST_CASE( "uniformly invoke any function-like object" )
{
    using namespace std;

    // lambda function
    auto add_l = []( int a, int b ) { return a + b; };

    // function wrapper
    std::function< int( int, int ) > add_f = add;  // works for add_l too

    // another function wrapper using a type alias
    using func = int( int, int );
    std::function< func > add_fa = add;  // works for add_l too

    CHECK_EQ( std::invoke( add, 1, 2 ), 3 );
    CHECK_EQ( std::invoke( add_l, 1, 2 ), 3 );
    CHECK_EQ( invoke( add_f, 1, 2 ), 3 );
    CHECK_EQ( invoke( add_fa, 1, 2 ), 3 );

    Foo foo;
    // member function must be invoked with an instance as the first arg
    // NOTE the use of &
    CHECK_EQ( invoke( &Foo::add, foo, 1, 2 ), 3 );
    CHECK_EQ( invoke( Foo::s_add, 1, 2 ), 3 );

    // prebuilt function objects
    CHECK_EQ( invoke( std::plus<>(), 1, 2 ), 3 );
}
