//
// Created by wein on 25/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <neither/either.hpp>
#include <neither/try.hpp>
#include <neither/maybe.hpp>

#include <vector>
#include <string>
#include <iostream>

// source:
// https://github.com/LoopPerfect/neither

TEST_CASE( "handle exception" )
{
    using namespace neither;

    auto _ = [] { return false; };

    auto unsafe = [ & ]() -> int {
        // a function that throws, sometimes we can't avoid it...
        throw std::runtime_error( "computation has failed" );
    };

    Either< std::exception, int > e =
        Try< std::exception >( unsafe );  // let's lift the exception into the typesystem

    e.left().map( []( auto const &e ) {
        std::cerr << e.what() << std::endl;
        return 1;
    } );  // print error if available

    int result =
        e.leftMap( []( auto ) { return 42; } )  // do nothing with exception and map to 42
            .rightMap( []( auto x ) {
                return x * 2;
            } )       // do further computation if value available
            .join();  // join both sides of either

    CHECK_EQ( result, 42 );
}

neither::Either< std::string, int > compute( int x )
{
    if ( x < 0 )
    {
        return neither::left( std::string{ "don't pass x<0" } );
    }
    return neither::right( x * x );
}

TEST_CASE( "either monadic bind" )
{
    using namespace neither;
    std::string resultString =
        compute( 5 )
            .rightMap( []( auto x ) { return x / 2.0; } )  // success case
            .join(
                []( auto errorStr ) {
                    return "compute said: " + errorStr;
                },  // error-case
                []( auto x ) {
                    return "compute said: " + std::to_string( x );
                }  // success-case
            );

    std::cout << resultString << std::endl;
}

neither::Maybe< float > computeMaybe( float x )
{
    if ( x < 0 )
        return {};
    return { sqrtf( x ) };
}

TEST_CASE( "maybe example" )
{
    using namespace neither;

    auto x = computeMaybe( -4 ).map( []( auto x ) { return x * x; } ).map( []( auto x ) {
        return x + 1;
    } );

    if ( !x.hasValue )
    {
        std::cerr << "error occured" << std::endl;
    }
}