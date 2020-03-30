#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <numeric>
#include <vector>

TEST_CASE("copy: copy vector of int") {
    std::vector elems{5, 4, 3, 2, 1};

    // L595 borrow Groovy's approach that uses first class function
    // (copy_if) to run more FP code
    std::vector evenElems(0, 0);
    std::copy_if(elems.cbegin(), elems.cend(), std::back_inserter(evenElems),
                 [](const auto &v) { return v % 2 == 0; });

    CHECK(6 == std::accumulate(evenElems.cbegin(), evenElems.cend(), 0));
}