//
// Created by weining on 28/3/20.
//

#include "test_utilities.h"

#include <iostream>
#include <algorithm>
#include <vector>

struct Name {
    std::string first;
    std::string last;

    bool operator==(const Name &other) const {
        return first == other.first && last == other.last;
    }

    bool operator!=(const Name &other) const {
        return ! operator==(other);
    }

    // need this if I want to print the object in the panic message
    // reference:
    // https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
    // NOTE: it has to be a friend free function with two explicit operands
//    friend std::ostream& operator<<(std::ostream &os, const Name &self) {
//        os << self.first << " " << self.last;
//        return os;
//    }

};

int main(int argc, char *argv[]) {
    // source: FP with C++ L528
    std::vector elems{5, 4, 3, 2, 1};
    std::sort(elems.begin(), elems.end());
    assert_vector_eq(elems, {1, 2, 3, 4, 5});

    // FP with C++ L535
    std::vector names{Name{"e1", "m1"}, Name{"e2", "m2"}};
    std::sort(names.begin(), names.end(), [](const Name &lhs, const Name &rhs) {
        return lhs.first < rhs.first;
    });

    // L562
    assert_vector_eq(names, {{"e1", "m1"}, {"e2", "m2"}});
}