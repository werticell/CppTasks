#include <iostream>
using std::cout;

template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

/* теперь попытка вызвать например такую функцию
 * для типа, который не является классом, вызовет ошибку компиляции
 */
template<typename T, typename  = typename enable_if<std::is_class<T>::value, T>::type>
void g(const T& x) {
    cout << 1;
}


