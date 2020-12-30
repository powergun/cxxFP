//
// Created by weining on 7/12/20.
//
// FP in C++ P/7
// the intro section compares the imperative impl of git_cloc (count lines per file) with
// the FP one; the latter uses the STL transform and subsequently range-v3's pipe
// operator; this example shows how to use the pipe operator from the range library - how
// to construct views and consume the views

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <string_view>
#include <ranges>
#include <algorithm>

#include <range/v3/all.hpp>

int count_lines( const std::string &filename )
{
    std::ifstream in( filename );
    return std::count( std::istreambuf_iterator< char >( in ),
                       std::istreambuf_iterator< char >(),
                       '\n' );
}

std::vector< int > count_lines_in_files( const std::vector< std::string > &filenames )
{
    // see range-v3 manual:
    // https://ericniebler.github.io/range-v3/index.html#tutorial-views
    // views::... must be converted to the STL container in order to return, use the to<>
    // template
    using namespace ranges;
    return filenames | views::transform( count_lines ) | to< std::vector >;
}

int total_lines( const std::vector< std::string > &filenames )
{
    using namespace ranges;
    return accumulate( filenames | views::transform( count_lines ), 0 );
}

TEST_CASE(
    "use pipe operator to express fmap (views); use ranges::to to consume the result "
    "(views)" )
{
    auto cloc = count_lines_in_files( { "/etc/passwd", "/etc/passwd", "/etc/passwd" } );
    CHECK_EQ( cloc.size(), 3 );
    CHECK( cloc[ 0 ] == cloc[ 2 ] );
    CHECK( cloc[ 0 ] == cloc[ 1 ] );
    CHECK_GT( cloc[ 0 ], 10 );
}

TEST_CASE( " use ranges::accumulate to consume the result (views)" )
{
    auto cloc = total_lines( { "/etc/passwd", "/etc/passwd", "/etc/passwd" } );
    CHECK_GT( cloc, 30 );
}

// c++ 20 the programmer's intro P/151
// this version looks cleaner and FP

TEST_CASE( "is palindrome impl with cxx range api" )
{
    auto is_letter = []( char ch ) { return std::isalpha( ch, std::locale{} ); };
    auto to_lowercase = []( char ch ) { return std::tolower( ch, std::locale() ); };
    auto f = [ & ]( std::string_view sv ) -> bool {
        auto letters_only{ sv | std::views::filter( is_letter ) };
        auto in_lowercase{ letters_only | std::views::transform( to_lowercase ) };
        auto reversed{ in_lowercase | std::views::reverse };
        return std::ranges::equal( in_lowercase, reversed );
    };

    CHECK( f( "e1m1xxxx1m1e" ) );
}