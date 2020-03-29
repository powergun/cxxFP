#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <functional>

// hands on FP with C++ L1418
std::function<int(int)> compose1(std::function<int(int)> f, std::function<int(int)> g) {
    return [f, g](auto x) { return f(g(x)); };
}

template<typename F, typename G>
auto compose2(F f, G g) {
    return [=](auto x) { return f(g(x)); };
}

TEST_CASE ("demo: compose by explicit typing") {
    CHECK_EQ(10, compose1([](auto x) { return x + 3; }, [](auto x) { return x + 7; })(0));
}

struct Item {};

TEST_CASE ("demo: compose by template") {
    // type check is still performed at compile time, try replace x + 3 with Item{} and see
    // the compiler error
    CHECK_EQ(10, compose2([](auto x) { return x + 3; }, [](auto x) { return x + 7; })(0));
}
