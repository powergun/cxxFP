//
// Created by weining on 19/4/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/istream_range.hpp>

#include <sstream>
#include <vector>
#include <iterator>
#include <typeinfo>

#include <range/v3/all.hpp>

#include <ranges>

// source:
// https://theboostcpplibraries.com/boost.range-helper-classes-and-functions

template < typename T >
class TypeTester;

TEST_CASE( "copy the value read from the input stream to a sink (output stream)" )
{
    // NOTE:
    // using both libraries, I can avoid creating the temporary vector, by directly copy()
    // the source (istream_iterator) to the sink (ostream_iterator)
    // recall it is a recipe in some c++ book as the implementation of a cheap "echo"
    // program
    {
        using namespace boost;

        std::vector< int > v;
        v.reserve( 10 );
        std::stringstream ss( R"( 123 1
                                 3 4
                                )" );
        iterator_range< std::istream_iterator< int > > ir = istream_range< int >( ss );
        boost::copy( ir, std::back_inserter( v ) );

        boost::copy( v, std::ostream_iterator< int >{ std::cout, " " } );
        std::cout << '\n';
    }
    {
        // range-v3
        std::stringstream ss( R"( 123 1
                                 3 4
                                )" );
        auto ir = ranges::istream_view< int >( ss );
        // ir is of type:
        // ranges::istream_view<int>
        // TypeTester<decltype(ir)>(); // btw. typeid() does not give me a readable form
        ranges::copy( ir, std::ostream_iterator< int >{ std::cout, " " } );
        std::cout << '\n';
    }
    {
        // c++ ranges api
        std::stringstream ss( R"( 123 1
                                 3 4
                                )" );
        auto ir = std::ranges::istream_view< int >( ss );
        std::ranges::copy( ir, std::ostream_iterator< int >{ std::cout, " " } );
        std::cout << '\n';
    }
}