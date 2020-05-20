//
// Created by weining on 20/5/20.
//

// TODO: implement tuple type-list meta-functions
// IsEmpty
// Front
// PopFront
// PushFront
// PushBack
// InsertionSort

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <tuple>
#include <iostream>

// c++ template: complete guide L20129
// NOTE: this is the implemention copied from
// https://stackoverflow.com/questions/17178075/how-do-i-reverse-the-order-of-element-types-in-a-tuple-type
// I simplified it by removing the remove_reference<> metafunc, and changing all the
// forwarding reference to const reference, but the idea stays the same:
// use fold expression and constexpr arithmetic to calculate the reverse
// index list, then use the select-idiom (explained c++ template: complete guide)
// to project the solution - the new order - onto the original tuple.
template<typename... Elements, size_t... Indices>
auto reverse_impl(const std::tuple<Elements...> &tu, std::index_sequence<Indices...>) {
    //                                                            0 1 2 3
    return std::make_tuple(std::get<sizeof...(Indices) - 1 - Indices>(tu)...);
    //                                           3 2 1 0
}

template<typename... Elements>
auto reverse(const std::tuple<Elements...> &tu) {
    return reverse_impl(tu, std::make_index_sequence<sizeof...(Elements)>{});
}

// c++ template: complete guide L20266
// the select-idiom
template<typename... Elements, std::size_t... Indices>
auto select(const std::tuple<Elements...> &tu, std::index_sequence<Indices...>) {
    return std::make_tuple(std::get<Indices>(tu)...);
}

TEST_CASE ("test std::integer_sequence") {
    using namespace std;

    auto tu{make_tuple(10, 'x', false, 1.0)};
    make_integer_sequence<std::size_t, 4> iseq;
}

TEST_CASE ("reverse tuple") {
    using namespace std;

    auto tu{make_tuple(10, 'x', false, 1.0)};
    auto rtu{reverse(tu)};
    std::apply([](const auto &... elements) {
        ((cout << elements << " "), ...);
    }, rtu);
    cout << endl;
    CHECK_EQ(make_tuple(1.0, false, 'x', 10), rtu);
}

TEST_CASE ("select-idiom") {
    using namespace std;

    auto tu{make_tuple(10, 'x', false, 1.0)};

    // c++ template: complete guide L20266
    auto tu_{select(tu, std::index_sequence<0, 2>{})};
    CHECK_EQ(tu_, make_tuple(10, false));

    // splat()
    auto tuSplat{select(tu, std::index_sequence<2, 2, 2, 2>{})};
    CHECK_EQ(tuSplat, make_tuple(false, false, false, false));

}

TEST_CASE ("tuple cat") {
    using namespace std;

    auto tu{make_tuple(10, 'x', false, 1.0)};
    auto tux2{std::tuple_cat(tu, tu)};

    CHECK_EQ(tux2, make_tuple(10, 'x', false, 1.0, 10, 'x', false, 1.0));
}
