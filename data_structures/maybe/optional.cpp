#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <optional>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>
#include <complex>
#include <limits>

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
        // convert string to int, see:
        // https://www.techiedelight.com/convert-string-to-int-cpp/
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

TEST_CASE( "create optional values" )
{
    // C++ 17 in detail P/77

    // empty

    std::optional< std::string > _empty;
    // I can explicitly assign an empty value to nullify a non-empty optional value,
    // recall Rust's take() method
    std::optional< std::string > _empty_too = std::nullopt;

    // non-empty, direct creation

    using Col = std::vector< int >;
    std::optional< int > _v1( 1 );
    std::optional _v2( 2 );  // deduce

    // non-empty, use std::make_optional();
    // make_optional implements the inplace construction, equivalent to
    // std::optional x{std::in_place, ...}

    auto _v22 = std::make_optional( 3.0 );
    auto _v33 = std::make_optional< std::complex< double > >( 3.0, 4.0 );

    // non-empty, in-place
    // in-place is the only option when the contained resource is NOT movable
    // or copyable such as std::mutex

    std::optional< Col > _vo{ std::in_place };  // no temp obj; Col is created in-place
    std::optional< std::complex< double > > _v44{ std::in_place, 3.0, 4.0 };
    std::optional< Col > _v55{ std::in_place, Col{ 1, 2, 3 } };

    // non-empty, created in the same way as the wrapped value

    std::optional< std::string > _v66{ "idkfa" };
    std::optional _v77{ Col{ 1, 2 } };  // deduce
    static_assert( std::is_same_v< decltype( _v77 ), std::optional< Col > > );
}

template < typename T >
std::optional< T > fmap( std::optional< T > &&opt )
{
    // NOTE: C++20 simplifies the lambda deduction, so I may be able
    // to turn this free function into a lambda;
    // see:
    // https://stackoverflow.com/questions/42799208/perfect-forwarding-in-a-lambda

    // C++ 17 in detail P/82
    // this also takes advantage of copy-elision
    if ( std::forward< std::optional< T > >( opt ).has_value()
         && std::forward< std::optional< T > >( opt ).value() > 0 )
    {
        // I can also use optional::value_or()
        return std::forward< std::optional< T > >( opt ).value() + 1;
    }
    else
    {
        return std::nullopt;
    }
}

TEST_CASE( "returning optional value by returning the wrapped value directly" )
{
    CHECK_EQ( fmap( std::optional< int >( 10 ) ), std::optional{ 11 } );
    CHECK_EQ( fmap( std::optional< int >( -10 ) ), std::optional< int >{} );
    CHECK_EQ( fmap( std::optional< int >{} ), std::optional< int >{} );
}

TEST_CASE( "mutate the contained value" )
{
    // c++ 17 in detail P/84
    // emplace, reset, swap and assign
}

TEST_CASE( "compare the contained value directly " )
{
    using O = std::optional< int >;
    CHECK_LT( O( 1 ), O( 2 ) );

    // empty optional value is always less than any non-empty value
    CHECK_LT( O(), O( std::numeric_limits< int >::min() ) );
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
