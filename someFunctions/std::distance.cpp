#include <iostream>
using std::cout;

template<typename Iterator, bool b>
struct distance_help {
    static int distance_impl(Iterator& it1, Iterator& it2) {
        return it2 - it1;
    }
};

template<typename Iterator>
struct distance_help<Iterator, false> {
    static int distance_impl(Iterator& it1, Iterator& it2) {
        int counter = 0;
        while(it1 != it2) {
            ++it1;
            ++counter;
        }
        return counter;
    }
};

template<typename Iterator>
int distance(Iterator& iter1, Iterator& iter2) {
    return distance_help<Iterator, std::is_same<typename std::iterator_traits<Iterator>::iterator_category,
            std::random_access_iterator_tag>::value>::distance_impl(iter1, iter2);
}

