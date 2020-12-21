//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// NOTE: there are a few examples of structured binding
//  - cxxFP/data_structure/ranges/factory_delimited
//  - cxxAlgorithms/map/efficient_map_access
//  - cxxFP/semantics/decompose/README.md
// But **this file** is the source of truth.

// C++17 in detail P/56
// declaring custom get<N> functions
// use structured binding syntax with classes that contain private data members

#include <utility>
#include <type_traits>

class Item
{
public:
    [[nodiscard]] int getA() const
    {
        return a;
    }
    [[nodiscard]] float getB() const
    {
        return b;
    }

private:
    int a;
    float b;
};

template < std::size_t I >
auto get( Item &x ) // provide mutable binding
{
    if constexpr ( I == 0 )
    {
        return x.getA();
    }
    else if constexpr ( I == 1 )
    {
        return x.getB();
    }
}

template < std::size_t I >
auto get( const Item &x ) // provide immut binding
{
    if constexpr ( I == 0 )
    {
        return x.getA();
    }
    else if constexpr ( I == 1 )
    {
        return x.getB();
    }
}

namespace std
{
template <>
struct tuple_size< Item > : std::integral_constant< size_t, 2 >
{
};

template <>
struct tuple_element< 0, Item >
{
    using type = int;
};

template <>
struct tuple_element< 1, Item >
{
    using type = float;
};

}  // namespace std

TEST_CASE( "structured binding from immutable instance" )
{
    Item x{};
    auto &[ a, b ] = x;

    static_assert( std::is_same_v< int, decltype( a ) > );
    a = 133;

    // x is immutable (because of const-method and return-by-value)
    CHECK_EQ( x.getA(), 0 );

    // add these mut-getter method for truly mutable binding:
    // int& getA()
    // float& getB()
}

// c++17 the complete guide P/6
// structured binding types
template < typename T >
struct TypeTester;
TEST_CASE( "structured bindings are of the type of the original member fields" )
{
    Item x{};
    const auto &[ a, b ] = x;

    // a, b are not references
    static_assert( std::is_same_v< const int, decltype( a ) > );
    static_assert( std::is_same_v< const float, decltype( b ) > );
}

// c++ 17 the complete guide P/8
// with structures and classes, all non-static data members must be members of
// the same class definition (thus, they have to be direct members of the type
// or of the same unambiguous public base class) - can not mix-match derived
// class members with the base class members

TEST_CASE( "assign new values to structured binding for pair and tuple" )
{
    // c++ 17 the complete guide P/10
    // use std::tie to reassign the existing bindings to a new value
    // this technique can be useful to model a for-loop:
    // for (auto [a, b] = some_value; b != EOF; std::tie(a, b) = new_value) {
    // }

    using Item = std::pair< int, int >;
    auto [ a, b ] = Item{ 1, 1 };

    std::tie( a, b ) = Item{ 2, 2 };
    CHECK_EQ( a, 2 );
    CHECK_EQ( b, 2 );
}

TEST_CASE( "nested binding not supported" )
{
    std::pair x{ std::pair( 1, 1 ), 1 };
    // does not support nested binding
    // auto &[[x, y], z] = x;
}