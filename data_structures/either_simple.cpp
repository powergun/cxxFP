//
// Created by weining on 12/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <variant>

// loosely based on FP in C++ P/188
// wrap Left and Right values in std::variant to simplify plumbing
// P189
// assignment of either value should take the `copy-and-swap` approach:
// create a temporary value of T
// if successful, swap the internal data with it
// if not, internal data is untouched

template < typename Left, typename Right >
struct Either
{
    template < typename... Args >
    static Either left( Args... params )
    {
        return Either( Left( std::forward< Args >( params )... ) );
    }

    template < typename... Args >
    static Either right( Args... params )
    {
        return Either( Right( std::forward< Args >( params )... ) );
    }

    [[nodiscard]] bool isLeft() const
    {
        // source:
        // https://en.cppreference.com/w/cpp/utility/variant/holds_alternative
        return std::holds_alternative< Left >( value );
    }

private:
    template < typename T >
    Either( T&& x ) : value( x )
    {
    }
    std::variant< Left, Right > value;
};

TEST_CASE( "construct left and right Either values" )
{
    using Result = Either< std::string, std::vector< int > >;
    auto err = Result::left( "an error" );
    auto success = Result::right( std::vector< int >{ 1, 2, 3 } );

    CHECK( err.isLeft() );
    CHECK_FALSE( success.isLeft() );
}