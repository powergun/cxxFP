//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <cctype>

// FP in c++ P/96
// this book mentions a few times function(al) lifting, and elaborates on this
// in chapter 4, where it lifts an f (to_upper) of `string -> string` to
// work with `string * -> string *`, even `M<string> -> M<string>`, M being
// a collection template

template < typename Function >
auto pointer_lift( Function f )
{
    return [ f ]( auto *item ) {
        if ( item )
        {
            f( *item );
        }
    };
}

template < typename Function >
auto collection_lift( Function f )
{
    return [ f ]( auto &xs ) {
        for ( auto &x : xs )
        {
            f( x );
        }
    };
}

void to_upper_mut( std::string &s )
{
    std::for_each( s.begin(), s.end(), []( auto &c ) { c = std::toupper( c ); } );
}

TEST_CASE( "lifting `T -> T` to the context of `M T -> M T`" )
{
    std::string s{ "there is a cow" };
    pointer_lift( to_upper_mut )( &s );
    CHECK_EQ( s, "THERE IS A COW" );

    std::vector< std::string > strings{ "there", "is", "a", "cow" };
    collection_lift( to_upper_mut )( strings );
    CHECK_EQ( strings, std::vector< std::string >{ "THERE", "IS", "A", "COW" } );
}