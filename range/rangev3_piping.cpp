//
// Created by weining on 12/5/20.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view.hpp>
#include <vector>
#include <range/v3/algorithm/transform.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/count.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>

// modern c++ programming cookbook L5024
// L5012
// simply put, a range is a traversable entity - has begin() and end(), much like
// the containers (every stl container can be treated as a range)
// stl algorithms are redefined to take ranges as direct arguments
//
// by doing this, they allow us to pass a result from one algorithm directly to
// the other instead of storing intermediary results in local variables

TEST_CASE ("compose transform and filter") {
    using namespace std;

    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    auto v_ = v | ranges::views::transform([](const auto &n) { return n * 2; })
                | ranges::views::filter([](const auto &n) { return n > 5; });
    copy(begin(v_), end(v_), ostream_iterator<int>{cout, " "});
    cout << endl;
}

namespace Item {

    static int creation = 0;
    static int deletion = 0;

    struct Item {
        int value{0};
        explicit Item(int v): value(v) {
            creation++;
        }
        ~Item() {
            deletion++;
        }
    };
    template<typename T>
    class TT;
    TEST_CASE ("test object life time") {
        using namespace std;

        // without reserve(6), the entire vector will relocate due to the growing size, which triggers object deletion
        vector<Item> items; items.reserve(6);
        items.emplace_back(0); items.emplace_back(1); items.emplace_back(2);
        items.emplace_back(0); items.emplace_back(1); items.emplace_back(2);
        CHECK_EQ(6, creation);
        CHECK_EQ(0, deletion);
        auto new_rng = items | ranges::views::transform([](const auto &i) { return Item{i.value * 2}; })
                             | ranges::views::filter([](const auto &i) { return i.value > 2; });
        // range is lazy evaluated, meaning that at this stage, transform() and filter does not take effect
        // counter remains 6 (no new object creation/deletion activities)
        //
        // also read: modern c++ programming cookbook L5048
        // filter: apply the pred function at incr/decr op
        // transform: apply the function at elem-read op
        CHECK_EQ(6, creation);
        CHECK_EQ(0, deletion);

        // consume the range, trigger evaluation
         for_each(begin(new_rng), end(new_rng), [](const auto &_) {});

        // transform() will create 6 more items, counter = 12
        // filter will collect 4 items, resulting in a new 2-item range,
        // for_each() will consume this range, triggering the actual creation (of these 2 items), hence counter = 14
        CHECK_EQ(14, creation);

        // the internally created 6 items by transform() are discarded
        // those 4 items not selected by filter() are also discarded
        // therefore there are 10 calls to dtor()
        CHECK_EQ(10, deletion);
    }

}

