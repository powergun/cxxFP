//
// Created by weining on 15/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <ranges>

// range-v3's to<> and to_vector were not selected by the C++ standard, therefore c++20's
// range api expects the user to roll her own version;
// this example shows one possible implementation
// source:
// https://stackoverflow.com/questions/63115900/c20-ranges-view-to-vector

// this is a critical missing piece that makes the c++20 ranges api almost unusable,
// such as in the case of schwartzian transform
// (Schwartz: https://www.pronouncenames.com/Schwartz)

// NOTE: I can use the same logic to implement a to_string() template - converting a (split)
// view to a string

template < std::ranges::range R >
auto to_vector( R&& r )
{
    auto r_common = r | std::views::common;
    return std::vector( r_common.begin(), r_common.end() );
}

TEST_CASE( "test to_vector" )
{
    {
        // used as a normal function template
        auto v = to_vector( std::ranges::iota_view{ 1, 5 } );
    }
    {
        // can't compile
        // std::ranges::iota_view{ 1, 5 } | to_vector;
    }
}
