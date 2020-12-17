//
// Created by weining on 17/12/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <unistd.h>
#include <iostream>

struct Resource
{
    Resource()
    {
        sleep( 1 );
    }
};

// C++ 17 in detail P/76
// I can use std::optional<> to model lazy resource (delayed loading)

TEST_CASE( "optional lazy loading" )
{
    // observe how creating the optional value does not trigger the creation of the
    // contained resource
    std::optional< Resource > optRes;
    std::cout << "created std::optional value" << '\n';
    std::cout.flush();

    // explicitly create the contained resource
    optRes.emplace();
    std::cout << "called std::optional::emplace(), construct the contained value in-place"
              << '\n';
}