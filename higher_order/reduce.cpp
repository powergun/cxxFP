//
// Created by weining on 28/3/20.
//

#include "test_utilities.h"

#include <vector>
#include <numeric>
#include <iostream>

void RunTinyTests();


void test_sum() {
    std::vector<int> elems{1, 2, 3, 4, 5};
    assert_eq(15, std::accumulate(elems.cbegin(), elems.cend(), 0));
}

void test_conditional_sum() {
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
    assert_eq(6, result);
}

int main(int argc, char *argv[]) {
    RunTinyTests();
    return 0;
}