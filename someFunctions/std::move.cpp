template<typename T>
std::remove_reference_t<T> move( T&& other) {
    return static_cast<typename std::remove_reference_t<T> &&>(other);
}

