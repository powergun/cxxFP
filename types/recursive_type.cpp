//
// Created by weining on 24/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <optional>
#include <memory>
#include <vector>

// c++ 17 the complete guide P/291
// std::vector<> can support incomplete type
//

struct Node;

using OptNode = std::optional< Node >;
using NodeVec = std::vector< Node >;

// won't compile; std::optional<> does not support incomplete type (in recursion)
// struct Node
//{
//    OptNode next;
//};

using NodePtr = std::shared_ptr< Node >;

// I can use this new feature to model tree, linked-list

struct Node
{
    NodePtr next{ nullptr };
    NodeVec ns{};
};

TEST_CASE( "vector with incomplete type" )
{
    Node n{ nullptr, { Node{}, Node{} } };
    //             ^ next  ^ ns
}