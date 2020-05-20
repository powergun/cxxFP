//
// Created by weining on 20/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <tuple>
#include <iostream>
#include <sstream>

// print() impl borrowed from:
// https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple

template<std::size_t Index = 0, typename... Elements>
inline typename std::enable_if_t<Index == sizeof...(Elements)>
prt(std::ostream &os, const std::tuple<Elements...> &t) {
}

template<std::size_t Index = 0, typename... Elements>
inline typename std::enable_if_t<Index < sizeof...(Elements)>
prt(std::ostream &os, const std::tuple<Elements...> &t) {
    // use this to verify the template instantiation
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    os << std::get<Index>(t);
    if constexpr (Index < sizeof...(Elements) - 1) {
        os << ", ";
    }
    prt<Index + 1, Elements...>(os, t);
    //^^^^^^^^^^^^^^^^^^^^^^^^
    // instantiate to print<0, x>, print<1, x>, print<2, x> .... print<N, x>
    // the last one is the base case
}

template<typename... Elements>
std::ostream &operator<<(std::ostream &os, const std::tuple<Elements...> &tu) {
    os << "<";
    prt(os, tu);
    os << ">";
    return os;
}

// base case
template<std::size_t Index = 0, typename F, typename... Elements>
std::enable_if_t<(Index == sizeof...(Elements))>
visit(const std::tuple<Elements...> &tu, F f) {}

template<std::size_t Index = 0, typename F, typename... Elements>
std::enable_if_t<(Index < sizeof...(Elements))>
visit(const std::tuple<Elements...> &tu, F f) {
    f(std::get<Index>(tu));
    visit<Index + 1, Elements...>(tu, f);
}

TEST_CASE ("print tuple") {
    using namespace std;
    ostringstream oss;
    oss << make_tuple(1, 'a', "asd", false);
    CHECK_EQ(oss.str(), "<1, a, asd, 0>");
}

TEST_CASE ("visit tuple elements") {
    // it doesn't matter if visitor function F has all the overloads
    // the visit function can only instantiate (the first) one

    // the difference in print-tuple function is that, operator<<
    // refers to the free functions for each Element type, it is
    // not threaded by the recursive call chain (i.e. passing the
    // function object into the function template)
}