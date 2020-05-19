//
// Created by weining on 19/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <tuple>
#include <vector>

using Elem = std::tuple<int, int, int>;
using Stream = std::vector<Elem>;

template<typename T>
using SubStream = std::vector<T>;

template<typename Head, typename... Tail>
std::tuple<std::vector<Head>, std::vector<Tail>...>
split(const std::vector<std::tuple<Head, Tail...>> &s) {
    // TODO: impl
    return {};
}

TEST_CASE ("") {
    Stream s{{1, 2, 3},
             {2, 4, 6},
             {1, 3, 5}};
    auto subs = split(s);
    static_assert(
        std::is_same_v<
            decltype(subs),
            std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>
        >
    );
}
