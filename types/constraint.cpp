
// with clang-10, I can not include <concept> header

// modern c++ programming cookbook L4615
// a constraint is a way to specify requirements for template arguments, and
// as follows, a concept is a set of constraints
// use the && operator to combine several concepts into one

// see also: https://en.cppreference.com/w/cpp/experimental/constraints

#include <iostream>

template<typename T>
concept addable = requires (T obj) { obj + obj; };

template<addable T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    using namespace std;
    cout << sum(1, 2) << endl;
    cout << sum('a', 'b') << endl;
    return 0;
}
