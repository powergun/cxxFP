//
// Created by weining on 9/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <functional>
#include <boost/phoenix.hpp>
#include <range/v3/all.hpp>
#include "../vendor/auto_timer.h"

// FP in c++ P/66 mentions boost::phoenix library while explaining the generic lambdas;
// also at DA, I've heard of the author of this library;
// this example shows how to make use of it

TEST_CASE( "std::partition with phoenix argument" )
{
    // FP in c++ P/66
    // stl lambda makes it easier for the compiler to optimize
    // boost::phoenix slows down compilation

    using namespace boost::phoenix::arg_names;
    std::vector< int > xs{ 3, 1, 4, 1, 5, 9, 2, 6 };
    std::stable_partition( xs.begin(), xs.end(), arg1 <= 5 );
    CHECK_EQ( xs, std::vector< int >{ 3, 1, 4, 1, 5, 2, 9, 6 } );

    // some quick and dirty perf comparison (gcc/clion warns that std::bind is bad)
    //  stl lambda 1,474 micro-secs
    //  stl bind less-than 8,947 micro-secs
    //  boost::phoenix 6,210 micro-secs
    {
        auto nums = ranges::iota_view{ 0, 100000 } | ranges::to< std::vector< int > >();
        // use a lambda function
        {
            AutoTimer atm( "stl lambda" );
            std::stable_partition(
                nums.begin(), nums.end(), []( const auto &x ) { return x < 4999; } );
        }
    }
    {
        auto nums = ranges::iota_view{ 0, 100000 } | ranges::to< std::vector< int > >();
        // use a std::less_than and std::bind
        AutoTimer atm( "stl bind less-than" );
        std::stable_partition(
            nums.begin(), nums.end(), std::bind( std::less<>(), std::placeholders::_1, 4999 ) );
    }
    {
        auto nums = ranges::iota_view{ 0, 100000 } | ranges::to< std::vector< int > >();
        // use phoenix lib
        {
            AutoTimer atm( "boost::phoenix" );
            std::stable_partition( nums.begin(), nums.end(), arg1 <= 4999 );
        }
    }
}
