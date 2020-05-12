
// can not include <concept> header

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
