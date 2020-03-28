//
// Created by weining on 28/3/20.
//

#ifndef CXXFP_TEST_UTILITIES_H
#define CXXFP_TEST_UTILITIES_H

#include <iostream>
#include <sstream>
#include <vector>

void panic(const std::string &msg) {
    // inspiration: https://stackoverflow.com/questions/19369002/is-there-a-c-equivalent-to-phps-var-dump-and-die
    // unlike golang and perl C++ does not have such a handy termination function
    std::cerr << msg << std::endl;
    exit(1);
}

template<typename T>
void assert_eq(const T &lhs, const T &rhs) {
    if (lhs != rhs) {
        std::stringstream ss;
        ss << "lhs != rhs" << std::endl;
        panic(ss.str());
    }
}

template<typename T>
void assert_vector_eq(const std::vector<T> &lhs, const std::vector<T> &rhs) {
    // some inspiration here:
    // https://stackoverflow.com/questions/12552277/whats-the-best-way-to-iterate-over-two-or-more-containers-simultaneously
    // zip iterator is not available in C++ 17
    // but here is a short example: https://codereview.stackexchange.com/questions/231352/c17-zip-iterator-compatible-with-stdsort
    // also: https://stackoverflow.com/questions/8511035/sequence-zip-function-for-c11
    std::stringstream ss;
    if (lhs.size() != rhs.size()) {
        // C++ 17 still does not have string interpolation
        ss << "lhs.size " << lhs.size() << " != " << "rhs.size " << rhs.size() << std::endl;
        panic(ss.str());
    }
    ss.clear();
    unsigned int idx{0};
    for (const auto &a : lhs) {
        if (a != rhs[idx]) {
            ss << "idx " << idx << ", lhs.element != rhs.element" << std::endl;
            panic(ss.str());
        }
        idx++;
    }
}

#endif //CXXFP_TEST_UTILITIES_H
