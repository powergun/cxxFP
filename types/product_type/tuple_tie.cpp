//
// Created by weining on 12/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <tuple>
#include <iostream>

// FP in C++ P/176
// std::tie creates tuple of references of the original values

// for example, if you have a class that holds a person's name and surname,
// and you want to implement a less-than operator for it to compare the
// surname first and then the name,

struct Person
{
    std::string surname;
    std::string name;

    Person( std::string &&s, std::string &&n ) : surname( s ), name( n )
    {
    }
};

bool operator<( const Person &l, const Person &r )
{
    return std::tie( l.surname, l.name ) < std::tie( r.surname, l.name );
}

TEST_CASE( "use tie to create tuple of references (mutable ref)" )
{
    std::vector< Person > xs{ { "xguy", "doom xguy" }, { "nukem", "john nukem" } };
    std::sort( xs.begin(), xs.end() );
    CHECK_EQ( xs[ 0 ].surname, "nukem" );

    int a = 1;
    int b = 2;
    auto tu = std::tie( a, b );
    // https://en.cppreference.com/w/cpp/utility/tuple
    // recall Scala uses ._N notation
    std::get< 0 >( tu ) = 12;
    CHECK_EQ( a, 12 );
}
