#include <algorithm>
#include <iostream>
#include <vector>

struct Name {
  std::string first;
  std::string last;
};

int main(int argc, char *argv[]) {
  // source: FP with C++ L528
  std::vector elems{5, 4, 3, 2, 1};
  std::sort(elems.begin(), elems.end());
  std::cout << elems.size() << std::endl;

  // FP with C++ L535
  std::vector names{Name{"e1", "m1"}, Name{"e2", "m2"}};
  std::sort(names.begin(), names.end(), [](const Name lhs, const Name rhs) {
    return lhs.first < rhs.first;
  });

  // L562
  for (auto it = names.cbegin(); it != names.cend(); ++it) {
    std::cout << it->first << " " << it->last << std::endl;
  }
  return 0;
}
