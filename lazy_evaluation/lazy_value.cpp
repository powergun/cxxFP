//
// Created by weining on 10/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <optional>
#include "../vendor/auto_timer.h"

// FP in c++ P/124
// there are a few brilliant points:
// - note how it uses std::optional
//   because it uses std::optional, it does not need a boolean flag to indicate
//   whether the computation has been performed
//   also it does not require the wrapped return value to be default-constructable
//   if I store the return value T directly, this can be a problem
// - note how it uses decltype(auto) to deduce the return type (which is actually
//   a reference to the wrapped return value)
// - it is thread safe thanks to the mutex

// see his implementation, references/fcpp-code-examples/chapter-06/lazy-val/main.cpp
// where he defines a macro that makes the lazy value acts more like Scala expression
// block:
// lazy {
//   ...
//   return .
// }

template < typename Function >
class LazyVal
{
public:
    explicit LazyVal( Function f ) : m_function{ f }
    {
    }

    decltype( auto ) operator()()
    {
        if ( !m_result )
        {
            // FP in C++ P/126
            // instead of using a mutex, I can use std::call_once which is
            // thread-safe.
            std::lock_guard< std::mutex > lock( m_value_lock );
            m_result = std::invoke( m_function );
        }
        return *m_result;
    }

private:
    Function m_function;
    mutable std::optional< decltype( m_function() ) > m_result;
    mutable std::mutex m_value_lock;
};

int fib( int a )
{
    return a > 2 ? fib( a - 1 ) + fib( a - 2 ) : 1;
}

TEST_CASE( "wrap a computation to form a lazy value" )
{
    auto lv = LazyVal( []() -> int { return fib( 2 ); } );
    CHECK_EQ( 1, lv() );

    auto expensive = LazyVal( []() -> auto { return fib( 40 ); } );
    for ( const auto &_ : std::vector< int >{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } )
    {
        // expect the computation (fib) to run only once;
        CHECK_GT( expensive(), 10 );
    }
}

TEST_CASE( "prof the lazy evaluation" )
{
    //  strict evaluation 23,262 micro-secs
    //  lazy evaluation 24,988 micro-secs
    // the overhead comes from the function invocation;
    // but if I need to book keep the lazy values for a longer period of time
    // I have to deal with additional overhead comes from storage
    {
        // use normal strict evaluation
        std::vector< int > xs( 1000, 20 );
        {
            AutoTimer atm( "strict evaluation" );
            std::transform( xs.cbegin(), xs.cend(), xs.begin(), []( const auto &x ) {
                return fib( x );
            } );
        }
    }
    {
        // use lazy evaluation
        std::vector< int > xs( 1000, 20 );
        {
            AutoTimer atm( "lazy evaluation" );
            std::transform( xs.cbegin(), xs.cend(), xs.begin(), []( const auto &x ) {
                return LazyVal( [ x ]() { return fib( x ); } )();
            } );
        }
    }
}