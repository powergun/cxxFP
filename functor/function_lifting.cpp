//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <cctype>
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

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

// c++ 17 the  complete guide P/76
// the example here provides another aspect of `lifting` similar to a state monad:
// (haskell)
// newtype State s a = State { runState :: s -> (a, s) }
//
// given a pure function T -> T, I can create a call-count state monad and its `runState`
// function:
// runState: M c -> (ret, M c')
// c and c' is the call count before/after a call to T -> T

// this is empowered by the c++ 17 template argument deduction and std::ref()

template < typename Function >
class CountCalls
{
public:
    explicit CountCalls( Function fun ) : f( fun )
    {
    }

    template < typename... Ts >
    auto operator()( Ts &&...params )
    {
        ++calls;
        return f( std::forward< Ts >( params )... );
    }

    [[nodiscard]] auto count() const
    {
        return calls;
    }

private:
    Function f;
    size_t calls{ 0 };
};

TEST_CASE( "wrap pure function in call count class" )
{
    // use std::ref(func) to ensure the same function object is invoked by
    // all the sort steps (because std::sort only uses the counter of its
    // own copy of the passed counter - it takes the function object by
    // value)
    CountCalls counter{ []( const auto &a, const auto &b ) { return a > b; } };
    std::vector xs{ 3, 1, 4, 1, 5, 9, 2, 6 };
    std::sort( xs.begin(), xs.end(), std::ref( counter ) );

    std::copy( xs.cbegin(), xs.cend(), std::ostream_iterator<int>{ std::cout, ", " } );
    std::cout << '\n' << counter.count() << '\n';
}