//
// Created by weining on 28/3/20.
//

#include "test_utilities.h"

#include <algorithm>
#include <numeric>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector elems{5, 4, 3, 2, 1};

    // L595 borrow Groovy's approach that uses first class function
    // (copy_if) to run more FP code
    std::vector evenElems(0, 0);
    std::copy_if(elems.cbegin(), elems.cend(), std::back_inserter(evenElems),
                 [](const auto &v) { return v % 2 == 0; });

    assert_eq(6, std::accumulate(evenElems.cbegin(), evenElems.cend(), 0));
    return 0;
}