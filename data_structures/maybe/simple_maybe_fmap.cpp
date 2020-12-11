//
// Created by weining on 7/12/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <optional>
#include <functional>

template < typename T >
struct Maybe
{
    std::optional< T > value;

    static Maybe some( T x )
    {
        return { std::optional< T >( x ) };
    }

    static Maybe none()
    {
        return { std::optional< T >() };
    }

    template < typename R >
    Maybe fmap( std::function< R( T ) > fun )
    {
        if ( value.has_value() )
        {
            return { std::optional< R >( fun( *value ) ) };
        }
        return { std::optional< T >() };
    }
};

TEST_CASE( "implement fmap() for maybe" )
{
    auto m1 = Maybe< int >::some( 1 );
    auto m2 = Maybe< int >::none();

    auto m1_ = m1.fmap< long >( []( int x ) { return x + 1; } ).fmap< char >( []( long x ) {
        return '\0';
    } );
    auto m2_ = m2.fmap< long >( []( int x ) { return x + 1; } ).fmap< char >( []( long x ) {
        return '\0';
    } );

    CHECK_EQ( *m1_.value, '\0' );
    CHECK_FALSE( m2_.value.has_value() );
}