//
// Created by weining on 13/1/21.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <functional>
#include <utility>
#include <variant>
#include <string>
#include <memory>
#include <iostream>

// inspired by the article `Programs as Values` from the zio document
// https://zio.dev/docs/overview/overview_background

// the immutable values doesn't do nothing - it just describes a program
// that prints out a message, asks for input etc...
// we can translate the model into procedural effects using an interpreter,
// which recurses on the data structure, translating every instruction
// into the side-effect that it describes

template < typename T >
struct Return;
template < typename T >
using PReturn = std::shared_ptr< Return< T > >;
template < typename T >

struct PrintLine;
template < typename T >
using PPrintLine = std::shared_ptr< PrintLine< T > >;

template < typename T >
struct ReadLine;
template < typename T >
using PReadLine = std::shared_ptr< ReadLine< T > >;

template < typename T >
using Console = std::variant< PReturn< T >, PPrintLine< T >, PReadLine< T > >;

template < typename T >
struct Return
{
    using ValueType = T;
    using F = std::function< T() >;

    Return() : f( []() { return T(); } )
    {
    }
    explicit Return( T arg ) : f( [ arg ]() { return arg; } )
    {
    }

    F f;
};

template <>
struct Return< void >
{
    using ValueType = void;
    using F = std::function< void() >;
    Return() = default;
    F f{ []() { ; } };
};

template < typename T >
struct PrintLine
{
    using ValueType = T;

    PrintLine() = delete;
    PrintLine( std::string l, Console< T > c )
        : line( std::move( l ) ), rest( std::move( c ) )
    {
    }

    std::string line{};
    Console< T > rest;
};

template < typename T >
struct ReadLine
{
    using ValueType = T;
    using F = std::function< Console< T >( std::string ) >;

    ReadLine() = delete;
    explicit ReadLine( F fun ) : f( std::move( fun ) )
    {
    }

    F f;
};

// interpreting (aka running or executing) is not functional, because it
// may be partial, non-deterministic and impure.
// in an ideal application, interpretation only needs to happen once:
// in the application's main function
// the rest of the application can be purely functional

template < typename T >
T interpret( const Console< T >& c )
{
    if ( std::holds_alternative< PReturn< T > >( c ) )
    {
        return std::get< PReturn< T > >( c )->f();
    }
    else if ( std::holds_alternative< PPrintLine< T > >( c ) )
    {
        const auto& p = std::get< PPrintLine< T > >( c );
        std::cout << p->line << '\n';
        return interpret( p->rest );
    }
    else if ( std::holds_alternative< PReadLine< T > >( c ) )
    {
        const auto& r = std::get< PReadLine< T > >( c );
        return interpret( r->f( "hardcoded input" ) );
    }
    else
    {
        // C++ compiler does not know pattern matching is exhaustive
        return T();
    }
}

template < typename T >
auto succeed( T a ) -> Console< T >
{
    return std::make_shared< Return< T > >( a );
}

auto succeed() -> Console< void >
{
    return std::make_shared< Return< void > >();
}

// composing these leaf instructions into larger programs becomes a lot
// easier if define `map` and `flatMap`
// (NOTE: I defined these as free functions)
//

// NOTE: unlike the example in the zio tutorial, the return type has to be Console<int>
// in order to be compatible with flatMap();
// flatMap() takes a function of R(T), but T can not be `void`;
// another way to solve this problem is to specialize the flatMap() function template with
// <void, R> (T = void)
auto putStrLn( const std::string& line ) -> Console< int >
{
    return std::make_shared< PrintLine< int > >( line, succeed< int >( 0 ) );
}

template < typename T >
auto readLine() -> Console< T >
{
    return std::make_shared< ReadLine< T > >(
        //
        []( const std::string& line ) -> auto { return succeed< T >( line ); } );
}

template < typename T, typename R >
auto flatMap( const std::function< Console< R >( T ) >& f, const Console< T >& c )
    -> Console< R >
{
    if ( std::holds_alternative< PReturn< T > >( c ) )
    {
        return f( std::get< PReturn< T > >( c )->f() );
    }
    else if ( std::holds_alternative< PPrintLine< T > >( c ) )
    {
        const auto& p = std::get< PPrintLine< T > >( c );
        return std::make_shared< PrintLine< R > >( p->line, flatMap( f, p->rest ) );
    }
    else if ( std::holds_alternative< PReadLine< T > >( c ) )
    {
        const auto& r = std::get< PReadLine< T > >( c );
        return std::make_shared< ReadLine< R > >(
            [ r, f ]( const std::string& line ) -> auto {
                return flatMap( f, r->f( line ) );
            } );
    }

    // to fool the compiler
    return Console< R >();
}

template < typename T, typename R >
auto map( std::function< R( T ) > f, const Console< T >& c ) -> Console< R >
{
    return flatMap< T, R >(
        [f]( T a ) -> auto { return succeed( f( a ) ); }, c );
}

// FP: instead of interacting with the real world, they build a functional
// effect, which is nothing more than an immutable, type-safe, tree-like
// data structure that models procedural effects
// FP programmers use functional effects to build complex, real world software
// without giving up the equation reasoning, composability and type safety
// afforded by pure FP

TEST_CASE( "compose program using constructors" )
{
    auto example = std::make_shared< PrintLine< int > >(
        //
        "hello",
        std::make_shared< ReadLine< int > >(
            //
            []( const std::string& name ) -> auto {
                return std::make_shared< PrintLine< int > >(
                    //
                    "received: " + name,
                    std::make_shared< Return< int > >() );
            } ) );
    auto o = interpret< int >( example );
    CHECK_EQ( 0, o );
}

TEST_CASE( "compose program using generator and flatMap" )
{
    // I wasn't able to implement an "operator template" that simulates the
    // the bind >>= operator; here is one explanation:
    // https://stackoverflow.com/questions/4014294/operator-overloading-on-class-templates
    // the fully instantiated operator definition must be known to the
    // compiler at the call site.

    auto s = interpret( readLine< std::string >() );
    CHECK_EQ( "hardcoded input", s );

    interpret( putStrLn( "idkfa" ) );

    auto echo = flatMap< std::string, int >(
        []( const std::string& l ) -> auto { return putStrLn( l ); },
        readLine< std::string >() );
    interpret( echo );

    auto doublePrint = flatMap< int, int >(
        []( int ) -> auto { return putStrLn( "there is a cow" ); },
        putStrLn( "there is a silence" ) );
    interpret( doublePrint );
}

TEST_CASE( "test fmap" )
{
    auto s = readLine< std::string >();
    auto t = map< std::string, size_t >(
        []( const std::string& s ) -> auto { return std::size( s ); }, s );
    CHECK_EQ( interpret( t ), 15 );
}
