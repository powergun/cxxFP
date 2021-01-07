//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <any>
#include <vector>
#include <algorithm>
#include <list>

// c++ stl cookbook P/355
// I don't think std::any expresses the concept of Maybe but it does have the similar
// mechanism as std::optional
// the `if type == typeid(...)` part is just wrong and nasty; not FP at all

enum class Types
{
    Integer,
    String,
    Double,
    Character,
    Pointer,
};

auto gen( const std::initializer_list< Types > &il )
{
    std::vector< std::any > v;
    for ( const auto &x : il )
    {
        if ( x == Types::Integer )
        {
            v.emplace_back( int{} );
        }
        else if ( x == Types::String )
        {
            v.emplace_back( std::string{ "" } );
        }
        else if ( x == Types::Double )
        {
            v.emplace_back( 0.0 );
        }
        else if ( x == Types::Character )
        {
            v.emplace_back( ' ' );
        }
        else
        {
            v.emplace_back( std::any{} );
        }
    }
    return v;
}

TEST_CASE( "cons-list any" )
{
    std::list< std::any > l{ 1, false, 1.0f };
}

TEST_CASE( "test any as Maybe" )
{
    auto v = gen( { Types::Pointer, Types::String, Types::Integer } );
    CHECK_FALSE( v[ 0 ].has_value() );
    CHECK_EQ( v[ 1 ].type(), typeid( std::string ) );
    CHECK_EQ( v[ 2 ].type(), typeid( int ) );
}