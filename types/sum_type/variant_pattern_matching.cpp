//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <variant>
#include <optional>

// C++ 17 in detail P/106
// this section shows an interesting use case of the `overload` lambda pattern:
// to implement the haskell-like pattern matching that works with multiple
// sum-types (or a single sum-type)
// the key point is, how to implement the "default case" using a generic lambda
// which is least favored by the compiler, hence is only called when all the
// other specifically-typed lambdas reject the given pattern.

struct IceCream
{
};
struct Chocolate
{
};

using Ingredient = std::variant< IceCream, Chocolate >;
using Shake = std::optional< int >;

template < typename... Ts >
struct overload : Ts...
{
    using Ts::operator()...;
};

template < typename... Ts >
overload( Ts... ) -> overload< Ts... >;

Shake shake( const Ingredient& i1, const Ingredient& i2 )
{
    /**
     * case (i1, i2) of
     *   IceCream{...}, Chocolate{...} -> Some 1
     *   _, _ -> None
     *
     * */
    auto o = std::visit(
        overload( []( const IceCream&, const Chocolate& ) -> Shake { return 10; },
                  []( const auto&, const auto& ) -> Shake { return std::nullopt; } ),
        i1,
        i2 );
    return o;
}

TEST_CASE( "demo haskell-like pattern matching" )
{
    // input pattern is matched; a non-empty optional value is returned
    CHECK_EQ( Shake{ 10 }, shake( Ingredient{ IceCream{} }, Ingredient{ Chocolate{} } ) );

    // input pattern falls to the ground; an empty optional value is returned
    CHECK_EQ( Shake{}, shake( Ingredient{ IceCream{} }, Ingredient{ IceCream{} } ) );
}

template < typename Num >
struct Constant
{
    Num value;
};

template < typename Num >
struct Linear
{
    Num begin;
    Num end;
};

template < typename T >
using Param = std::variant< Constant< T >, Linear< T > >;

template < typename T >
Param< T > makeConstant( T x )
{
    Constant< T > c{};
    c.value = x;
    return c;
}

template < typename T >
Param< T > makeLinear( T a, T b )
{
    Linear< T > lin{};
    lin.begin = a;
    lin.end = b;
    return lin;
}

template < typename T >
T beginV( const Param< T >& param )
{
    // NOTE:
    // I can not use the generic overload() framework here;
    // it seems that if the variant has a generic type parameter, it will fail to create
    // the overload callable.
    // in the production code (autotimer) I ended up using inheritance and virtual function
    // to model the polymorphism, but the code below also works (same runtime overhead)

    return std::visit(
        []( const Param< T >& param ) -> T {
            if ( std::holds_alternative< Constant< T > >( param ) )
            {
                return std::get< Constant< T > >( param ).value;
            }
            else if ( std::holds_alternative< Linear< T > >( param ) )
            {
                return std::get< Linear< T > >( param ).begin;
            }
            else
            {
                return T{};
            }
        },
        param );
}

TEST_CASE( "pattern matching when types have generic type parameter" )
{
    auto linear = makeLinear( 1, 10 );
    auto constant = makeConstant( 10 );
    CHECK_EQ( 10, beginV( constant ) );
    CHECK_EQ( 1, beginV( linear ) );
}
