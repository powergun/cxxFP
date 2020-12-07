#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <optional>
#include <vector>
#include <string>
#include <sstream>

using Texts = std::vector< std::string >;
using Nums = std::vector< int >;
using OptNums = std::optional< Nums >;

// inspired by hands on FP with C++, L2414
// see:
// https://en.cppreference.com/w/cpp/utility/optional
OptNums conv( const Texts &ts )
{
    Nums ns{};
    ns.reserve( ts.size() );
    for ( const auto &t : ts )
    {
        // convert string to int, see: https://www.techiedelight.com/convert-string-to-int-cpp/
        try
        {
            ns.emplace_back( std::stoi( t ) );
        }
        catch ( std::invalid_argument const &e )
        {
            return std::nullopt;
        }
        catch ( std::out_of_range const &e )
        {
            return std::nullopt;
        }
    }
    return ns;
}

TEST_CASE( "optional: emulate maybe type" )
{
    auto ns1 = conv( { "10", "asd", "" } );
    CHECK( !ns1.has_value() );
    // c++ stl cookbook P/341
    // instead of always writing has_value(), we can also write if(x) {}
    CHECK_FALSE( ns1 );

    auto ns2 = conv( { "999999999999999999999999999999999999999999999", "99" } );
    CHECK( !ns2.has_value() );

    auto ns3 = conv( { "1", "3", "7" } );
    CHECK( ns3.has_value() );
    CHECK_EQ( Nums{ 1, 3, 7 }, ns3 );
}

TEST_CASE( "optional fallback" )
{
    // check out value_or() method!
    auto ns1 = conv( { "," } ).value_or( Nums{} );
    CHECK_EQ( 0, ns1.size() );

    auto ns2 = conv( { "1", "2" } ).value_or( Nums{} );
    CHECK_EQ( 2, ns2.size() );
    CHECK_EQ( Nums{ 1, 2 }, ns2 );
}

struct Item
{
    std::size_t sz{};
    double weight{};
};

std::optional< Item > parse( std::istream &is )
{
    Item i;
    if ( is >> i.sz >> i.weight )
    {
        return i;
    }
    return {};
}

TEST_CASE( "optional wraps struct" )
{
    // if we have a struct foo {} type and want to access one of its members
    // through an optional<Foo> value, then we can write x->a
    std::stringstream ss{ "102 3.13" };
    if ( auto v = parse( ss ); v )
    {
        CHECK_EQ( v->sz, 102 );
    }
    else
    {
        CHECK( false );
    }
}
