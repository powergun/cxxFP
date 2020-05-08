//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <tuple>
#include <functional>

// c++ stl cookbook P/344
// std::apply is a compile time helper that helps us work more agnostic about
// the types we handle
//

bool foo(const std::string &, double, int) {
    return true;
}

TEST_CASE ("") {
    using namespace std;
    auto items = {
        make_tuple("e1m1", 1.0, 1),
        make_tuple("e1m2", 1.2, 2),
    };
    for (const auto &item : items) {
        CHECK(apply(foo, item));
    }
}
