#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <optional>
#include <vector>
#include <string>

using Texts = std::vector<std::string>;
using Nums = std::vector<int>;
using OptNums = std::optional<Nums>;

// inspired by hands on FP with C++, L2414
// see:
//https://en.cppreference.com/w/cpp/utility/optional
OptNums conv(const Texts &ts) {
    Nums ns{};
    ns.reserve(ts.size());
    for (const auto &t : ts) {
        // convert string to int, see: https://www.techiedelight.com/convert-string-to-int-cpp/
        try {
            ns.emplace_back(std::stoi(t));
        }
        catch (std::invalid_argument const &e) {
            return std::nullopt;
        }
        catch (std::out_of_range const &e) {
            return std::nullopt;
        }
    }
    return ns;
}

TEST_CASE("optional: emulate maybe type") {
    auto ns1 = conv({"10", "asd", ""});
    CHECK(!ns1.has_value());

    auto ns2 = conv({"999999999999999999999999999999999999999999999", "99"});
    CHECK(!ns2.has_value());

    auto ns3 = conv({"1", "3", "7"});
    CHECK(ns3.has_value());
    CHECK_EQ(Nums{1, 3, 7}, ns3);

    // check out value_or() method!
}