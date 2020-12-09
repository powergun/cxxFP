//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <functional>

// c++ stl cookbook P/155
// this recipe also shows how to implement a framework that apply a function
// to any number of arguments (variadic) even the standard does not natively
// support the fold expression on it

// auto apply_multi(Ts ...args, Fs ...functions) {
//
// }

// this requires the following technique, decltype(auto)
// FP in c++ P/48
// when you are writing generic functions that forward the result of another
// function without modifying
// in this case you don't know in advance what function will be passed to you,
// and you can't know whether you should pass its result back to the caller
// as a value or as a ref

// decltype(auto) is the decltype of the returned expression

// this is also the core of "perfect forwarding" - recall this section in Modern Effective C++

template < typename T, typename R >
R apply( std::function< R( T ) > f, T t )
{
    return f( t );
}

int fValueValue( int x )
{
    return x + 1;
}

int fRefValue( int &x )
{
    return x + 1;
}

struct Item
{
    int value{ 0 };
};

int &fRefRef( Item &item )
{
    item.value += 1;
    return item.value;
}

TEST_CASE( "use decltype(auto) to pass function-value's return value back to the caller" )
{
    int x = 1;
    int o1 = apply< int, int >( fValueValue, x );
    int o2 = apply< int &, int >( fRefValue, x );
    CHECK_EQ( o1, 2 );
    CHECK_EQ( o2, 2 );

    Item item;
    CHECK_EQ( item.value, 0 );
    auto &o3 = apply< Item &, int & >( fRefRef, item );
    CHECK_EQ( item.value, 1 );
    ++o3;
    CHECK_EQ( item.value, 2 );
}

// another core technique is universal reference (aka forwarding reference)
// FP in C++ P/48
// provide a generic function that takes f which is a function that "works on the given object o";
// however, it is not known whether o will be a mutable ref or immutable
// and this is where forwarding-reference handles both situation gracefully

template < typename Object, typename Function >
decltype( auto ) applyTo( Function f, Object &&o )
{
    return f( std::forward< Object >( o ) );  // don't forget std::forward<>
}

int fConstRefValue( const int &x )
{
    return x + 1;
}

TEST_CASE( "use forwarding/universal reference to overcome the const-or-non-const ref issue" )
{
    int x = 1;
    auto o1 = applyTo( fConstRefValue, x );
    auto o2 = applyTo( fRefValue, x );

    CHECK_EQ( o1, 2 );
    CHECK_EQ( o2, 2 );
}

// FP in c++ P/60
// NOTE, perfect forwarding works slightly differently with generic lambda, which does not have
// the name of the type (it is auto instead)
// the generic lambda is a class with a template member function operator()(); itself is not a
// class template
// the lambda will deduce the type for each of its arguments that were declared
// as auto when it is called, not when it is constructed;
// the same lambda can be used on completely different types;
TEST_CASE( "forwarding reference and generic lambda function" )
{
    auto lApply = []( auto f, auto &&o ) -> decltype( auto ) {
        return f( std::forward< decltype( o ) >( o ) );
    };
    lApply( fValueValue, 1 );
    lApply( fConstRefValue, 1 );
    {
        int x = 1;
        lApply( fRefValue, x );
    }
}

TEST_CASE ("template parameter list for generic lambda (C++20)") {
    // FP in C++ P/61
    // generic lambda now supports template parameter list; however this requires the compiler (gcc)
    // to support this C++20 feature; I have not tested this on clang

    // note: compile fine with gcc-9
    //    auto ff = []< typename T >( T a ) -> T { return a + 1; };
    //    ff(1);

}