//
// Created by weining on 8/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <range/v3/all.hpp>
#include <utility>

// functional programming in C++ P/36

// this example is to demonstrate STL 's limitation in composing filter and map functions;
// the user of STL has to resort to copy_if or the erase-remove idiom to create a
// intermediate collection (filtering) and then use STL transform to create the
// destination collection (map)

// the range library overcomes this issue by providing the pipe operator and views

// however this is not a design flaw in STL; the merits of the iterator-based algorithms
// allow the user to work with different collection types simultaneously; for example the
// source collection can be a std::unordered_set<> while the dest collection can be a
// deque.

struct Item
{
    std::string name;
    int value;

    Item( std::string name, int value ) : name( std::move( name ) ), value( value )
    {
    }

    static std::vector< Item > create(
        std::initializer_list< std::pair< std::string, int > > il )
    {
        std::vector< Item > xs;
        xs.reserve( il.size() );
        for ( auto &pr : il )
        {
            xs.emplace_back( pr.first, pr.second );
        }
        return xs;
    }
};

TEST_CASE( "express filter map using STL algorithms " )
{
    auto xs = Item::create( { { "laser blade", 100 },
                              { "rail pistol", 230 },
                              { "shotgun", 30 },
                              { "assault rifle", 50 } } );

    std::vector< Item > valuables;
    valuables.reserve( xs.size() );
    std::copy_if(
        xs.cbegin(), xs.cend(), std::back_inserter( valuables ), []( const Item &item ) {
            return item.value > 80;
        } );

    std::vector< std::string > itemNames( valuables.size() );
    std::transform(
        valuables.cbegin(), valuables.cend(), itemNames.begin(), []( const Item &item ) {
            return item.name;
        } );

    CHECK_EQ( itemNames[ 0 ], "laser blade" );
    CHECK_EQ( itemNames[ 1 ], "rail pistol" );
}

TEST_CASE( " express filter map using range-v3 library" )
{
    auto xs = Item::create( { { "laser blade", 100 },
                              { "rail pistol", 230 },
                              { "shotgun", 30 },
                              { "assault rifle", 50 } } );

    using namespace ranges;
    auto trashes = xs
                   | views::filter( []( const Item &item ) { return item.value < 80; } )
                   | views::transform( []( const Item &item ) { return item.name; } )
                   | to< std::vector< std::string > >();

    CHECK_EQ( trashes[ 0 ], "shotgun" );
    CHECK_EQ( trashes[ 1 ], "assault rifle" );
}