//
// Created by weining on 11/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <range/v3/all.hpp>
#include <sstream>
#include <iostream>
#include <cctype>

// FP in C++ P/156
// a good recap on the word frequency problem, using only the range library
// constructs: views, actions and algorithms;
// NOTE:
// - it provides a useful helper function to create a view from an input stream
// - pay attention to how the string transformer functions are implemented
// - one of the less used algorithm: group_by

std::string toLower( const std::string &s )
{
    return s | ranges::views::transform( tolower ) | ranges::to< std::string >();
}

std::string removeUnwantedChars( const std::string &s )
{
    return s | ranges::views::filter( isalnum ) | ranges::to< std::string >();
}

TEST_CASE( "process istream via range library (the word frequency problem)" )
{
    using namespace ranges;
    std::stringstream ss{ R"(
There Is A
COW. There
is A Silence,
There is,
No Spoon.
)" };

    std::vector< std::string > xs =
        istream_view< std::string >( ss ) | views::transform( toLower )
        | views::transform( removeUnwantedChars )
        | views::remove_if( &std::string::empty ) | to< std::vector< std::string > >();
    xs |= actions::sort;
    auto o = xs | views::group_by( std::equal_to<>() )
             | views::transform( []( const auto &group ) {
                   auto a = std::begin( group );
                   auto b = std::end( group );
                   return std::make_pair( std::distance( a, b ), *a );
               } )
             | to_vector | actions::sort | actions::reverse;
    for ( const auto &[ fr, word ] : o )
    {
        std::cout << word << ": " << fr << '\n';
    }
}