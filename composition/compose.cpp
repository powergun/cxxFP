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

// modern c++ programming cookbook L3628
// implement a composition operator

template<typename F, typename G>
auto compose(F &&f, G &&g) {
    return [=](auto x) { return f(g(x)); };
}

template<typename F, typename G>
auto operator*(F &&f, G &&g) {
    return compose(std::forward<F>(f), std::forward<G>(g));
}

//template<typename F, typename... R>
//auto compose(F &&f, R &&...r) {
//    return [=](auto x) { return f(compose(r...)(x)); };
//}
//
//template<typename F, typename... R>
//auto operator*(F &&f, R &&... r) {
//    return compose(std::forward<F>(f), r...);
//}

TEST_CASE ("function composition operator") {
    auto f = [](int n) { return n + 1; }
           * [](int n) { return n * 10; };
    // f . g $ 5
    CHECK_EQ(f(5), 51);
}