//
// Created by weining on 7/12/20.
//
// FP in C++ P/7
// the intro section compares the imperative impl of git_cloc (count lines per file) with the FP
// one; the latter uses the STL transform and subsequently range-v3's pipe operator this example
// shows how to use the pipe operator from the range library

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <range/v3/all.hpp>

int count_lines( const std::string &filename )
{
    std::ifstream in( filename );
    return std::count(
        std::istreambuf_iterator< char >( in ), std::istreambuf_iterator< char >(), '\n' );
}

std::vector< int > count_lines_in_files( const std::vector< std::string > &filenames )
{
    // see range-v3 manual:
    // https://ericniebler.github.io/range-v3/index.html#tutorial-views
    // views::... must be converted to the STL container in order to return, use the to<> template
    using namespace ranges;
    return filenames | views::transform( count_lines ) | to< std::vector >;
}

TEST_CASE( "use pipe operator to express fmap" )
{
    auto cloc = count_lines_in_files({"/etc/passwd", "/etc/passwd", "/etc/passwd"});
    CHECK_EQ(cloc.size(), 3);
    CHECK(cloc[0] == cloc[2]);
    CHECK(cloc[0] == cloc[1]);
    CHECK_GT(cloc[0], 10);
}