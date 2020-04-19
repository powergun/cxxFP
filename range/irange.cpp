#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/range/irange.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>

#include <map>

int fib(int n) {
    if (n == 1 or n == 0) return 1;
    return fib(n - 1) + fib(n - 2);
}

TEST_CASE ("irange: python range()") {
    using namespace boost;

    // like python's, irange is exclusive, [0 , 10)
    CHECK_EQ(45, accumulate(irange(0, 10), 0, std::plus<int>{}));
}

TEST_CASE ("irange: generator") {
    using namespace boost;

    std::map<int, int> m;
    for_each(irange(0, 10), [&m](auto n) { m.insert({n, fib(n)}); });
    CHECK_EQ(55, max_element(m)->second);
    CHECK_EQ(min_element(m)->second, m[1]);
    CHECK_EQ(m[2], 2);
}
