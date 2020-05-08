//
// Created by weining on 8/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <variant>
#include <iostream>
#include <algorithm>

// c++ stl cookbook P/359

struct AdminLock {
};
struct UserLock {
};
struct OperatorLock {
};

using SecurityLock = std::variant<
    AdminLock,
    UserLock,
    OperatorLock>;

// P/361
// the most elegant way is variant::visit()
// this function accepts a function object and a variant instance
// the function object must implement different overloads for ALL the
// possible types the variant can hold
//
struct ProcessSecurityLock {
    void operator()(const AdminLock &al) {
        std::cout << "process: admin lock" << std::endl;
    }

    void operator()(const UserLock &ul) {
        std::cout << "process: user lock" << std::endl;
    }

    void operator()(const OperatorLock &ol) {
        std::cout << "process: operator lock" << std::endl;
    }
};

TEST_CASE ("the FP-way of dealing with variant") {
    for (const auto &l : {SecurityLock(AdminLock{}),
                          SecurityLock(UserLock{}),
                          SecurityLock(OperatorLock{})}) {
        std::visit(ProcessSecurityLock{}, l);
    }
}

// I can also use map, accumulate with sum type
TEST_CASE ("count num variants") {
    auto locks = {SecurityLock(AdminLock{}),
                  SecurityLock(UserLock{}),
                  SecurityLock(OperatorLock{})};
    auto num = std::count_if(std::begin(locks), std::end(locks),
        [](const auto &l) { return std::holds_alternative<AdminLock>(l); });
    CHECK_EQ(1, num);
}

// DON'T DO THESE:
//
//TEST_CASE ("") {
//    auto lock = []() {
//        return SecurityLock{UserLock{}};
//    };
//
//    for (const auto &l : {lock(), lock(), SecurityLock(OperatorLock{})}) {
//        if (std::holds_alternative<AdminLock>(l)) {
//                CHECK(false);
//        } else if (std::holds_alternative<UserLock>(l)) {
//            std::cout << "user lock" << std::endl;
//        } else if (std::holds_alternative<OperatorLock>(l)) {
//            std::cout << "operator lock" << std::endl;
//        }
//    }
//
//    for (const auto &l : {lock(), lock(), SecurityLock(OperatorLock{})}) {
//        if (auto al = std::get_if<AdminLock>(&l); al) {
//                CHECK(false);
//        } else if (auto ul = std::get_if<UserLock>(&l); ul) {
//            std::cout << "user lock" << std::endl;
//        } else if (auto ol = std::get_if<OperatorLock>(&l); ol) {
//            std::cout << "operator lock" << std::endl;
//        }
//    }
//}