//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <range/v3/all.hpp>
#include <numeric>

// with the range api, it is possible to construct schwartzian transform
// https://en.wikipedia.org/wiki/Schwartzian_transform
//

TEST_CASE( "using stl" )
{
    // not using the views but the stl collections - note how verbose the implementation is

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