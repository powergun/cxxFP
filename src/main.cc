#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Name {
  std::string first;
  std::string last;
};

// nested template parameter, see:
// https://stackoverflow.com/questions/20373466/nested-c-template-parameters-for-functions
// cpp reference:
// https://en.cppreference.com/w/cpp/language/template_parameters
// template and class keywords, since C++17 are interchangeable
// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
template <typename T, template <typename> typename CollectionType>
const T doSum(const CollectionType<T> &input, const T &init = 0) {
  return std::accumulate(input.cbegin(), input.cend(), init);
}

int main(int argc, char *argv[]) {
  // source: FP with C++ L528
  std::vector elems{5, 4, 3, 2, 1};
  std::sort(elems.begin(), elems.end());
  std::cout << elems.size() << std::endl;

  // FP with C++ L535
  std::vector names{Name{"e1", "m1"}, Name{"e2", "m2"}};
  std::sort(names.begin(), names.end(), [](const Name &lhs, const Name &rhs) {
    return lhs.first < rhs.first;
  });

  // L562
  for (auto it = names.cbegin(); it != names.cend(); ++it) {
    std::cout << it->first << " " << it->last << std::endl;
  }

  // L595 borrow Groovy's approach that uses first class function
  // (copy_if) to run more FP code
  std::vector evenElems(0, 0);
  std::copy_if(elems.cbegin(), elems.cend(), std::back_inserter(evenElems),
               [](const auto &v) { return v % 2 == 0; });
  std::cout << std::accumulate(evenElems.cbegin(), evenElems.cend(), 0)
            << std::endl;

  // pass a binary operator to std::accumulate
  // see: https://en.cppreference.com/w/cpp/algorithm/accumulate
  // NOTE: require C++20
  // the binary op is essentially AccT -> ElemT -> AccT (resemble left-fold)
  std::cout << std::accumulate(elems.cbegin(), elems.cend(), 0,
                               [](const auto &acc, const auto &elem) {
                                 return elem % 2 == 0 ? acc + elem : acc;
                               })
            << std::endl;
  // std::accumulate performs a left fold. In order to perform a right fold,
  // one must reverse the order of the arguments to the binary operator,
  // and use reverse iterators.
  // NOTE: the binary op remain the same (unlike Haskell's foldr)
  std::cout << std::accumulate(elems.rbegin(), elems.rend(), 0,
                               [](const auto &acc, const auto &elem) {
                                 return elem % 2 == 0 ? acc + elem : acc;
                               })
            << std::endl;

  return 0;
}
