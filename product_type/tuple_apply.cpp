//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <tuple>
#include <iostream>
#include <utility>
#include <algorithm>

// inspired by:
// https://medium.com/@matt.aubury/rip-index-sequence-2014-2017-9cc854aaad0
// this also resolves the type issue discovered in tuple.cpp that
// I can not effectively visit all the elements in a tuple
// another good utility offered by STL is:
// https://en.cppreference.com/w/cpp/utility/integer_sequence
// require C++14

template<typename... Elements>
std::ostream &operator<<(std::ostream &os, const std::tuple<Elements...> &tu) {
    // NOTE: f takes a parameter pack! instead of individual element. Must use
    //  the fold expression to handle the recursion
    std::apply(
        [&os](const auto &... elements) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            ((os << elements << " "), ...);
        },
        tu
    );
    return os;
}

TEST_CASE ("re-impl operator<< using tuple-apply idiom") {
    using namespace std;
    cout << make_tuple(1, false, 'a', "asd") << endl;
}

std::size_t op(int a) { return sizeof(a); }
std::size_t op(bool a) { return sizeof(a); }
std::size_t op(char a) { return sizeof(a); }
std::size_t op(const char *a) { return sizeof(a); }
template<typename T>
std::size_t op(T t) {
    // triggered by nullptr
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    return 0;
}

TEST_CASE ("return value from fold expression") {
    using namespace std;

    auto tu = make_tuple(1, false, 'a', "asd", nullptr);  // 4, 1, 1, 8
    auto s = std::apply(
        [](const auto &... elements) {
            // return (sizeof(elements) + ...);
            // op is statically polymorphic
            // it has to be a free function or a callable object
            // and there can be some fallback mechanism, such as the "wildcard" template
            // nullptr in the tuple is handled in the fallback
            return (op(elements) + ...);
        },
        tu
    );
    CHECK_EQ(s, 14);
}

template<typename... T1s, typename... T2s>
auto zip_tuples(const std::tuple<T1s...> &tu1, const std::tuple<T2s...> &tu2) {
    return std::apply([&](const auto &... lhs) {
        return std::apply([&](const auto &... rhs) {
            return std::tuple(std::pair(lhs, rhs)...);
        },
        tu2);
    },
    tu1
    );
}

TEST_CASE ("zip two tuples") {
    using namespace std;

    auto tu1{make_tuple(1, 'c', false, 7.62)};
    auto tu2{make_tuple(10, 'x', true, 12.7)};

    auto tu12{zip_tuples(tu1, tu2)};
    CHECK_EQ(std::get<2>(tu12).second, true);
}
