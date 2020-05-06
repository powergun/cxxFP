// require C++20 (clang-8+)
// initialize an automatic variable in the range-based for loop

#include <vector>
#include <iostream>

using namespace std;
int main() {
    vector<int> v{1, 2};
    for (int i = 0; auto &e : v) {
        std::cout << i + e;
    }
    return 0;
}
