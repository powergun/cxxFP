//
// Created by weining on 12/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <iostream>
#include <locale>
#include <iomanip>
#include <random>

#include <range/v3/all.hpp>
#include "../../vendor/auto_timer.h"

template < typename F >
void prof( std::vector< int > &v, std::vector< int > &o_v, F f, const std::string &l )
{
    AutoTimer t( l );
    f( v, o_v );
}

void stl_algorithm( std::vector< int > &v, std::vector< int > &not_used )
{
    using namespace std;
    auto f = [ mi = v.size() / 4, mx = v.size() / 4 * 3 ]( auto &elem ) {
        if ( elem < mi )
            elem = mi;
        else if ( elem > mx )
            elem = mx;
    };
    for_each( begin( v ), end( v ), f );
    partition( begin( v ), end( v ), [ mid = v.size() / 2 ]( const auto &elem ) {
        return elem < mid;
    } );
}

void range_algorithm( std::vector< int > &v, std::vector< int > &o_v )
{
    auto f = [ mi = v.size() / 4, mx = v.size() / 4 * 3 ]( const auto &elem ) -> int {
        if ( elem < mi )
            return mi;
        else if ( elem > mx )
            return mx;
        return elem;
    };
    auto v_ = v | ranges::views::transform( f )
              | ranges::views::filter(
                  [ half = v.size() / 2 ]( const auto &n ) { return n < half; } );
    std::copy( begin( v_ ), end( v_ ), begin( o_v ) );
}

void populate( std::vector< int > &v )
{
    std::default_random_engine engine( std::random_device{}() );
    std::uniform_int_distribution< int > dist( 0, v.size() );
    std::generate(
        std::begin( v ), std::end( v ), [ &dist, &engine ]() { return dist( engine ); } );
}

TEST_CASE( "simple comparison" )
{
    // NOTE: this is not fair - the version that uses range-v3 also calls std::copy which
    // brings considerable overhead!
    // see the more detailed comparison below under different categories (immut, mut etc.)
    std::vector< int > v( 1000000 );
    std::vector< int > o( 1000000 );
    populate( v );
    prof( v, o, stl_algorithm, "stl algorithm" );
    prof( v, o, range_algorithm, "range algorithm" );
}

TEST_CASE( "read only operation and immutable data" )
{
    // range wins:
    //
    //     readonly operator and immutable data: stl 259,318 micro-secs
    //    readonly operator and immutable data: range 11,311 micro-secs
    // readonly operator and immutable data: for-loop 12,635 micro-secs
    //
    using namespace ranges;
    constexpr size_t n = 1000000;
    std::vector< int > xs( n, 999 );
    {  // stl
        AutoTimer atm( "readonly operator and immutable data: stl" );
        auto os = xs | views::filter( []( const auto &x ) { return x > 100; } )
                  | to< std::vector< int > >();
        CHECK_EQ( os.size(), n );
    }
    {
        std::vector< int > os( xs.size() );
        {
            // range
            AutoTimer atm( "readonly operator and immutable data: range" );
            std::copy_if( xs.cbegin(), xs.cend(), os.begin(), []( const auto &x ) {
                return x > 100;
            } );
            CHECK_EQ( os.size(), n );
        }
    }
    {
        std::vector< int > os( xs.size() );
        {
            // raw for-loop
            AutoTimer atm( "readonly operator and immutable data: for-loop" );
            auto it = os.begin();
            for ( const auto &x : xs )
            {
                if ( x > 100 )
                {
                    *( it++ ) = x;
                }
            }
            CHECK_EQ( os.size(), n );
        }
    }
}