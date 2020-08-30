template<typename T>
struct remove_const { typedef T type; };

template<typename T>
struct remove_const<const T> { typedef T type;};

template <typename T>
using remove_const_t = typename remove_const<T>::type;


template<typename T>
struct remove_reference { typedef T type; };

template<typename T>
struct remove_reference<T&> { typedef T type; };

template<typename T>
struct remove_reference<T&&> { typedef T type; };

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;
