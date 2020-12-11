#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <utility>
#include <string>
#include <tuple>
#include <unordered_map>

// inspired by c++17 stl cookbook P/13
// also mentioned P/344

TEST_CASE( "unpack pair" )
{
    using namespace std;
    pair< int, string > p{ 1, "one" };
    auto &[ value, name ] = p;
    CHECK_EQ( value, 1 );
    CHECK_EQ( name, string{ "one" } );
    value = 10;
    CHECK_EQ( p.first, 10 );
}

TEST_CASE( "unpack tuple" )
{
    using namespace std;

    tuple< string, size_t, string > p{ "e1m1", 32, "hell's gate" };
    const auto &[ name, sz, desc ] = p;
    CHECK_EQ( name, string{ "e1m1" } );
    CHECK_EQ( sz, 32 );
    CHECK_EQ( desc, string{ "hell's gate" } );
}

struct Creature
{
    std::string name{};
    size_t code{ 0 };
};

struct Level
{
    std::string name{};
    size_t n_creatures{ 0 };
    Creature *creatures{ nullptr };
};

TEST_CASE( "unpack struct" )
{
    Level e1m1{ "hell's gate" };
    std::vector< Creature > e1m1_creatures{
        { "imp", 1001 },
        { "gunner", 1002 },
    };
    e1m1.n_creatures = e1m1_creatures.size();
    e1m1.creatures = e1m1_creatures.data();

    std::vector< Level > levels{ e1m1 };
    for ( const auto &[ name, n_creatures, creatures ] : levels )
    {
        for ( size_t i = 0; i < n_creatures; ++i )
        {
            CHECK( creatures[ i ].name.size() > 0 );
        }
    }

    // c++ stl cookbook P/15
    // when using structure bindings, we don't have std::tie dummy variables,
    // so we have to bind all the values to named variables.
    for ( const auto &[ name, _1, _2 ] : levels )
    {
        CHECK( name.size() > 0 );
    }
}

// c++ stl cookbook L603
// a lot of fundamental data structures in stl are immediately accessible using structural
// binding
TEST_CASE( "unpack map" )
{
    std::unordered_map< size_t, std::string > m{
        { 1001, "gunner" }, { 1002, "imp" }, { 1003, "commando" } };
    for ( const auto &[ code, name ] : m )
    {
        if ( code == 1002 )
            CHECK_EQ( name, "imp" );
    }
}
