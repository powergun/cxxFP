//
// Created by weining on 8/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <numeric>
#include "doctest/doctest.h"
#include "../../vendor/auto_timer.h"

// experiment with tailrec
// at the time of writing (gcc-9, c++17) tail call is NOT optimized BY DEFAULT;
// but it can enabled via a compiler flag:
// https://stackoverflow.com/questions/490324/how-do-i-check-if-gcc-is-performing-tail-recursion-optimization
// https://www.reddit.com/r/C_Programming/comments/4hazah/gcc_tailcall_recursion_optimization/
// https://dev.to/rohit/demystifying-tail-call-optimization-5bf3

int tailrecSum( const std::vector< int > &xs, size_t idx, int acc )
{
    if ( idx >= xs.size() )
    {
        return acc;
    }
    else
    {
        return tailrecSum( xs, idx + 1, acc + xs[ idx ] );
    }
}

TEST_CASE( "perf tailrec" )
{
    //   tailrec sum 2,272 micro-secs
    //  STL accumulate 716 micro-secs

    // NOTE! tail call is not optimized; it will cause stack overflow when the workload is sufficiently
    // large (1000000)
    std::vector< int > xs( 100000, 1 );
    {
        AutoTimer _( "tailrec sum" );
        tailrecSum( xs, 0, 0 );
    }
    {
        AutoTimer _( "STL accumulate" );
        std::accumulate( xs.cbegin(), xs.cend(), 0 );
    }
}