//
// Created by weining on 10/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <iostream>

// FP in c++ P/118
// recall that Rust also encourages this builder pattern
// the with_xxx() functions are called with rvalue reference - temporaries -
// hence it can use std::move() to move the ownership to `i` inside the
// function
// this enhance immutability (avoid setter() methods) and readability.

struct Item
{
    // FP in c++ P/118
    // making these data members `const` will disable the move mechanism;
    // therefore it is better to use const-member-function and const object.
    // this relates to the NRVO (named return value opt)

    std::string name;
    int value{};
    std::string description;

    Item()
    {
        std::cout << "called ctor" << '\n';
    }

    Item with_name( const std::string &s ) &&
    {
        Item i( std::move( *this ) );
        i.name = name;
        return i;
    }

    Item with_value( int x ) &&
    {
        Item i( std::move( *this ) );
        i.value = x;
        return i;
    }

    Item with_description( const std::string &s ) &&
    {
        Item i( std::move( *this ) );
        i.description = s;
        return i;
    }
};

TEST_CASE( "use builder pattern to `immutably modify` an object" )
{
    // observe the number of calls to the ctor (only 1)
    auto item = Item()
        .with_name("e1m1")
        .with_value(100)
        .with_description("there is a cow");

}