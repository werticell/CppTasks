#include <iostream>
using std::cout;

class someClass {
public:
    someClass() {}
    explicit someClass(int) {}
    someClass(int, int) {}
};


template <typename T, typename... Args>
struct is_constructible {
private:
    template <typename...>
    static int f(...) {
        return 0;
    }
    template <typename TT, typename... AArgs>
    static decltype(TT(AArgs()...), char()) f(int x) {
        return x;
    }
public:
    static const bool value = std::is_same<decltype(f<T, Args...>(0)), char>::value;
};

int main() {
    cout << is_constructible<someClass, int>::value;
    cout << is_constructible<someClass, int, int>::value;
    cout << is_constructible<someClass, int, int, int>::value;
    return 0;
}
