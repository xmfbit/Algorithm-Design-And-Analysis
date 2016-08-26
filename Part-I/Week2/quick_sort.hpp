#ifndef CLRS_QUICK_SORT_HPP
#define CLRS_QUICK_SORT_HPP

#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
namespace alg {
    size_t cnt = 0;
    template<typename Iterator>
    Iterator getMedian(const Iterator& first, const Iterator& median, const Iterator& last) {
      std::vector<Iterator> its{first, median, last};
      std::sort(its.begin(), its.end(), [&](const Iterator& lhs, const Iterator& rhs) {
        return *lhs < *rhs;
      });
      return its[1];
    }
    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    static Iterator _partition(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        cnt += last - first;
        // std::swap(*first, *last);   // In question 2, uncomment this line.

        //Iterator median = getMedian(first, first + (last - first) / 2, last);
        // std::swap(*first, *median);   // In question 3, uncomment these two lines.
        value_type p = *first;
        Iterator i = first + 1;
        for(Iterator j = first + 1; j <= last; ++j) {
          if(comp(*j, p)) {
            std::swap(*j, *i);
            ++i;
          }
        }
        std::swap(*first, *(i-1));
        return i-1;
    };

    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void quick_sort(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1) return;
        Iterator pivot_iter = _partition(first, last - 1, comp);
        quick_sort(first, pivot_iter, comp);
        quick_sort(pivot_iter+1, last, comp);
    };
} // end of namespace alg

#endif // end of file quick_sort.hpp
