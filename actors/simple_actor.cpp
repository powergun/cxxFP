//
// Created by weining on 12/1/21.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <functional>

// fp in C++ P/252
// an actor only knows how to receive a message and how to send a message
// onward.
// it can have as much private data as it needs to perform its work, but
// none of it should ever be available to the outside world
// NOTE: recall the rock jvm course: never break the encapsulation of an actor

// because the data can not be shared, you have no need for synchronization

// sink: only receive
// source: only send

template < typename MessageType, typename SourceMessageType >
struct Actor
{
    using ValueType = MessageType;
    virtual void processMessage( SourceMessageType&& message ) = 0;
    template < typename EmitFunction >
    void setMessageHandler( EmitFunction ){};
};

template < typename SourceMessageType >
struct Sink : public Actor< void, SourceMessageType >
{
    void processMessage( SourceMessageType&& message ) override
    {
    }
};

TEST_CASE( "" )
{
    ;
}
