//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/iterator/iterator_facade.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

//
// follow this guide:
// https://www.boost.org/doc/libs/1_69_0/libs/iterator/doc/iterator_facade.html

// NOTE:
// range library provides a shortcut to create infinite stream: views::ints

template < typename T >
class Stream
    : public boost::iterator_facade< Stream< T >, const T, boost::forward_traversal_tag >
{
public:
    Stream() = default;

    explicit Stream( T value ) : elem{ value }
    {
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
    }

    [[nodiscard]] bool equal( const Stream &other ) const
    {
        return this->elem == other.elem;
    }

    [[nodiscard]] const T &dereference() const
    {
        return elem;
    }

    const T elem{};
};

TEST_CASE( "simple test" )
{
    using namespace std;
    Stream s{ 12 };

    vector< int > v;
    copy_n( s, 3, back_inserter( v ) );
    CHECK_EQ( vector< int >{ 12, 12, 12 }, v );

    copy_n( s, 10, ostream_iterator< int >{ cout, " " } );
    cout << endl;
}
