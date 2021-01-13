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

auto putStrLn( const std::string& line ) -> Console< void >
{
    return std::make_shared< PrintLine< void > >( line, succeed() );
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

// template < typename T, typename R >
// auto map( std::function< R( T ) > f, const Console< T >& c ) -> Console< R >
//{
//    return flatMap< T, R >(
//        [f]( T a ) -> auto { return succeed( f( a ) ); }, c );
//}

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

TEST_CASE( "compose program using generator" )
{
    auto s = interpret( readLine< std::string >() );
    CHECK_EQ( "hardcoded input", s );

    interpret( putStrLn( "idkfa" ) );

    auto echo = flatMap< std::string, void >(
        []( const std::string& l ) -> auto { return putStrLn( l ); },
        readLine< std::string >() );
    interpret( echo );
}
