#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <vector>
#include <numeric>

TEST_CASE("demo: sum") {
    std::vector<int> elems{1, 2, 3, 4, 5};
    CHECK(15 == std::accumulate(elems.cbegin(), elems.cend(), 0));
}

TEST_CASE("demo: conditional sum") {
    std::vector<int> elems{1, 2, 3, 4, 5};
    // NOTE:
    // accumulate is NOT foldr as it does not use recursion
    // accumulate is an iterative approach, with a function that
    // happens to have a similar type signature to foldr's
    auto result = std::accumulate(elems.cbegin(), elems.cend(), 0,
                    [](const auto &acc, const auto &elem) {
                        // this shows the order of evaluation is first to last
                        // std::cout << acc << ", " << elem << std::endl;
                        return elem % 2 == 0 ? acc + elem : acc;
                    });
    CHECK(6 == result);
}
