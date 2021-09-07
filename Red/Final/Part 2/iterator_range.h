#pragma once

#include <algorithm>
using namespace std;

template <typename It>
class IteratorRange {
public:
    IteratorRange(It first, It last) : first(first), last(last) {
    }

    It begin() const {
        return first;
    }

    It end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

private:
    It first, last;
};

template <typename Container>
auto Head(Container& c, int top) {
    return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}


//template <typename Iterator>
//class Paginator {
//public:
//    Paginator(Iterator begin, Iterator end, size_t page_size) {
//        for (size_t range_size = end - begin; range_size;) {
//            size_t step = min(page_size, range_size);
//            pages.push_back({ begin,begin + step });
//            range_size -= step;
//            begin += step;
//        }
//
//    }
//
//    auto begin() const {
//        return pages.begin();
//    }
//
//    auto end() const {
//        return pages.end();
//    }
//
//    size_t size() const {
//        return pages.size();
//    }
//
//private:
//    vector<IteratorRange<Iterator>> pages;
//};
//
//template <typename C>
//auto Paginate(C& c, size_t page_size) {
//    return Paginator(c.begin(), c.end(), page_size);
//}