#include <iostream>
using std::cout;

template<typename Iterator>
void advance(Iterator it, int n) {
    advance_help<Iterator, std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>>(it, n);
}

template <typename Iterator, bool B>
struct adnvace_help {
    void advance_impl(Iterator it, int n) {
        for(int i = 0; i < n; ++i)
            ++it;
    }
};

template <typename Iterator>
struct adnvace_help<Iterator, true> {

    void advance_impl(Iterator it, int n) {
        it += n;
    }
};
