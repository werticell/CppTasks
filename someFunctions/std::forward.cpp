// T=Args; decltype(other) = Args&, вернет Args&&
// T=Args& ; decltype(other) = Args&; вернет Args&
template<typename T>
T&& forward(std::remove_reference_t<T>& other) {
    return static_cast<std::remove_reference_t<T>&&>(other);
}

