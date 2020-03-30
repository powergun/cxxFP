#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iterator>  // provide back_inserter
#include <vector>

using String = std::vector<char>;
using Item = std::pair<std::string, int>;

TEST_CASE ("transform: write to another vector") {
    // a good example that shows std::transform is NOT map:
    // if bcd is a zero-length vector, transform will cause segfault!
    String abc{'a', 'b', 'c'}, bcd(3, '\0'), cde{};
    std::transform(abc.cbegin(), abc.cend(), bcd.begin(),
                   [](const auto &elem) { return elem + 1; });
    CHECK_EQ(String{'b', 'c', 'd'}, bcd);

    // crash free
    cde.reserve(abc.size());
    std::transform(abc.cbegin(), abc.cend(), std::back_inserter(cde),
                   [](const auto &elem) { return elem + 2; });
    CHECK_EQ(String{'c', 'd', 'e'}, cde);

    // now, here is the horror show: mutating the data
    std::transform(abc.begin(), abc.end(), abc.begin(),
                   [](auto elem) { return std::toupper(elem); });
    CHECK_EQ(String{'A', 'B', 'C'}, abc);

    // f: [String] -> [Item]
    std::vector<String> bin{{'a', 'b'}, {'d', 'e'}};
    std::vector<Item> items{};
    items.reserve(bin.size());
    std::transform(bin.cbegin(), bin.cend(), std::back_inserter(items),
                   [](const auto &elem) { return Item{std::string(2, elem[0]), int(elem[1])}; });
    CHECK_EQ("aa", items[0].first);
}

// NOTE: this has a bug
//  >>> list(range(0, 1, 1000))
//[0]
std::vector<int> toRange(int start, int end, int incr=1) {
    std::vector<int> r((end - start) / incr, 0);
    for (auto &elem : r) {
        elem = start;
        start += incr;
    }
    return r;
}

TEST_CASE("range: generate range-like vector") {
    using Nums = std::vector<int>;
    CHECK_EQ(Nums{-4, -3, -2, -1}, toRange(-4, 0));
    CHECK_EQ(Nums{-4, -2}, toRange(-4, 0, 2));
    CHECK_EQ(Nums{7, 4}, toRange(7, 1, -3));
    CHECK_EQ(Nums{}, toRange(0, 0, 1000));
}
