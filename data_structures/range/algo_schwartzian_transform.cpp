//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <range/v3/all.hpp>
#include <numeric>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <utility>
#include <functional>
#include <unordered_map>

// with the range api, it is possible to construct schwartzian transform
// https://en.wikipedia.org/wiki/Schwartzian_transform
//

TEST_CASE( "using stl" )
{
    // not using the views but the stl collections - note how verbose the implementation
    // is

    std::string s{ "there  is   a cow  there     is a  silence  " };
    std::vector< std::string > xs;
    for ( size_t start = 0, end;
          ( end = s.find_first_of( ' ', start ) ) != std::string::npos;
          start = end + 1 )
    {
        if ( end - start > 0 )
        {
            xs.push_back( s.substr( start, end - start ) );
        }
    }

    std::unordered_map< std::string, size_t > dict;
    std::for_each( xs.cbegin(), xs.cend(), [ &dict ]( const auto &s ) {
        auto found = dict.find( s );
        if ( found == dict.cend() )
        {
            dict[ s ] = 1;
        }
        else
        {
            found->second += 1;
        }
    } );

    std::vector< std::pair< std::string, int > > ys;
    std::copy( dict.cbegin(), dict.cend(), std::back_inserter( ys ) );
    std::sort( ys.begin(), ys.end(), []( const auto &p1, const auto &p2 ) {
        return p1.second > p2.second;
    } );
    std::for_each( ys.cbegin(), ys.cend(), []( const auto &p ) {
        std::cout << p.first << ": " << p.second << '\n';
    } );
}

TEST_CASE( "warm-up: test ranges::views::groupby" )
{
    // group_by works by comparing the adjacent elements, therefore xs should be
    // pre-sorted see FP in C++ P/155 - I missed this detail.
    std::vector< std::string > xs{ "there", "is", "a", "cow", "there" };
    xs |= ranges::actions::sort;
    auto v =
        xs
        | ranges::views::group_by(
            []( const std::string &lhs, const std::string &rhs ) { return lhs == rhs; } )
        | ranges::to_vector;
    for ( const auto &g : v )
    {
        std::cout << *g.begin() << ": " << std::distance( g.begin(), g.end() ) << '\n';
    }
}

template < typename T >
class TypeTester;

TEST_CASE( "use range-v3 library" )
{
    // source:
    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2210r0.html
    // NOTE:
    // views::split() yields split_outer_iterator(), see the type detail below;
    // I need to transform() it back to std::string values for further processing;
    // to do that I can take advantage of the fact that, each individual segment is
    // also represented as "view" - hence piping it to the to<> template will work well

    std::string s{ "there  is   a cow  there     is a  silence  " };
    auto xs = s | ranges::views::split( ' ' )
              | ranges::views::filter( []( const auto &v ) { return !v.empty(); } )
              | ranges::views::transform(
                  []( const auto &v ) { return v | ranges::to< std::string >(); } )
              | ranges::to_vector;
    xs |= ranges::actions::sort;
    auto v = xs | ranges::views::group_by( std::equal_to<>() )
             | ranges::views::transform( []( const auto &grp ) {
                   // grp is of type: ranges::subrange
                   // TypeTester<decltype(grp)>();
                   const std::string &s = *grp.begin();
                   size_t count = std::distance( grp.begin(), grp.end() );
                   return std::make_pair( count, s );
               } )
             | ranges::to_vector | ranges::actions::sort;
    for ( const auto &[ count, word ] : v )
    {
        std::cout << word << ": " << count << '\n';
    }

    // for ( auto s : v )
    // {
    // v is of type:
    // ranges::detail::split_outer_iterator<
    //     ranges::split_view<
    //         ranges::ref_view< std::__cxx11::basic_string<char> >,
    //         ranges::single_view<char>
    //     >,
    //     true
    // >::value_type
    // TypeTester<decltype(s)>();
    // std::cout << '<' << s << '>' << '\n';
    // }
}
