//
// Created by weining on 9/12/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <memory>
#include <range/v3/all.hpp>

struct Session
{
    size_t id{ 1001 };
};

struct Item
{
    int payload{ 1 };

    static std::shared_ptr< Item > create()
    {
        return std::make_shared< Item >();
    }
};

TEST_CASE( "move ownership to non-copyable data to inside the lambda" )
{
    // FP in C++ P/60

    auto session = std::make_unique< Session >();
    // this won't compile: there is no copy-ctor for unique_ptr<Session>
    //    auto f = [session]() {
    //       ...
    //    };

    auto work = [ session = std::move( session ),
                  item = Item::create() ]( int numIterations ) -> size_t {
        for ( auto _ : ranges::iota_view{ 0, numIterations } )
        {
            session->id += item->payload;
        }
        return session->id;
    };

    // session is no longer valid (it has been consumed by the work lambda function)
    // recall this is similar to the Rust's call-by-consuming idiom
    CHECK_EQ( work( 5 ), 1006 );
}
