//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <array>

TEST_CASE ("") {
    using namespace std;

    array<int, 4> arr{1, 2, 3, 4};
    auto &[n1, n2, n3, n4] = arr;
    CHECK_EQ(4, n4);

    // there is no x:xs
}
