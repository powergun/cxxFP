//
// Created by weining on 11/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <random>
#include "../../vendor/auto_timer.h"
#include <range/v3/all.hpp>

// FP in C++ P/150
// range-actions are operations that mutate the source collection;
// it is the counterpart of view (read-only)
// perf when using range-actions is acceptable (see the comparison on sorting)

inline auto makeVecRand( size_t num, int mi, int mx )
{
    std::vector< int > xs( num, 0 );
    std::random_device rd;
    std::mt19937 g( rd() );
    std::uniform_int_distribution< int > dist( mi, mx );
    std::generate( xs.begin(), xs.end(), [ &g, &dist ]() mutable { return dist( g ); } );
    return xs;
}

TEST_CASE( "perf comparison: sort by range-actions v.s. sort by std::sort" )
{
    // it is almost a draw:
    //
    // sort by range-actions 36,829 micro-secs
    //   sort by std::sort() 24,174 micro-secs
    {
        std::vector< int > xs = makeVecRand( 100000, 1, 9999 );
        {
            // NOTE: range-action can not handle std::list, which does not have a
            // rand-access iterator
            AutoTimer atm( "sort by range-actions" );
            using namespace ranges;
            xs = std::move( xs ) | actions::sort;
        }
        CHECK_EQ( *xs.cbegin(), 1 );
    }
    {
        std::vector< int > xs = makeVecRand( 100000, 1, 9999 );
        {
            // NOTE: I can sort an std::list<> but range-actions can NOT!
            // to sort a list I need to use the its own method instead of the generic
            // one (std::sort)
            // source:
            // https://www.cplusplus.com/reference/list/list/sort/
            AutoTimer atm( "sort by std::sort()" );
            std::sort( xs.begin(), xs.end() );
        }
        CHECK_EQ( *xs.cbegin(), 1 );
    }
}
