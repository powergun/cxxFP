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

#endif //CXXFP_TEST_UTILITIES_H
