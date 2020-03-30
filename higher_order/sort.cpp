#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

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

TEST_CASE("sort: sort vector of int") {
    // source: FP with C++ L528
    std::vector elems{5, 4, 3, 2, 1};
    std::sort(elems.begin(), elems.end());
    CHECK(elems == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("sort: sort vector of Name objects") {
    // FP with C++ L535
    std::vector names{Name{"e3", "m1"}, Name{"e2", "m2"}};
    std::sort(names.begin(), names.end(), [](const Name &lhs, const Name &rhs) {
        return lhs.first < rhs.first;
    });

    // vector of the same type can be compared using ==
    // https://thispointer.com/c-how-to-compare-two-vectors-stdequal-comparators/
    // it uses std::equal template
    // { return (__x.size() == __y.size()
    //	      && std::equal(__x.begin(), __x.end(), __y.begin())); }
    CHECK(names == std::vector<Name>{{"e2", "m2"}, {"e3", "m1"}});
}
