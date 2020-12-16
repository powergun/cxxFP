//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

// NOTE: there are a few examples of structured binding (cxxFP/data_structure/ranges...
// and in cxxTemplate). This file is the source of truth.

// C++17 in detail P/56
// declaring custom get<N> functions
// use structured binding syntax with classes that contain private data members

#include <utility>

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
auto get( Item &x )
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

    a = 133;
    CHECK_EQ( x.getA(), 0 ); // x is immutable (because of const method)
}

