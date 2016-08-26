#ifndef CLRS_MERGE_SORT_HPP
#define CLRS_MERGE_SORT_HPP

#include <iterator>
#include <functional>

namespace alg {
    template <typename Iterator, typename Comp>
    static void merge(const Iterator& first, const Iterator& mid, const Iterator& last, const Comp& comp) {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        int len = last - first;
        value_type * aux = new value_type[len];

        Iterator p = first, q = mid;
        int k = 0;
        while(p != mid && q != last) {
            if(comp(*p, *q)) aux[k++] = *p++;
            else aux[k++] = *q++;
        }
        while(p != mid) {
            aux[k++] = *p++;
        }
        while(q != last) {
            aux[k++] = *q++;
        }

        for(int i = 0; i < len; ++i) {
            *(first + i) = aux[i];
        }
        delete [] aux;
    };

    template <typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void merge_sort(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1)   return;
        Iterator mid = (last - first) / 2 + first;
        merge_sort(first, mid, comp);
        merge_sort(mid, last, comp);
        merge(first, mid, last, comp);
    };

    /*
     * Get the count of inversion in an array by naive method, O(n^2)
     */
    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    int get_inversion_count_naive(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1)  return 0;
        int cnt = 0;
        for(Iterator it = first; it != last; ++it) {
            for(Iterator it_j = it + 1; it_j != last; ++it_j) {
                if(!comp(*it, *it_j))   cnt++;
            }
        }
        return cnt;
    };

    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void get_inversion_count_(size_t& cnt, const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        if(first == last || first == last - 1)  return;
        Iterator mid = (last - first) / 2 + first;
        get_inversion_count_(cnt, first, mid, comp);
        get_inversion_count_(cnt, mid, last, comp);
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        value_type * aux = new value_type[last - first];
        Iterator p = first, q = mid;
        size_t k = 0, left_len = mid - first;
        while(p != mid && q != last) {
            if(!comp(*p, *q))   {
                aux[k++] = *q++;
                cnt += left_len;
            } else {
                aux[k++] = *p++;
                left_len--;
            }
        }
        while(p != mid) {
            aux[k++] = *p++;
        }
        while(q != last) {
            aux[k++] = *q++;
        }
        for(Iterator it = first; it != last; ++it) {
            *it = aux[it - first];
        }
        delete [] aux;
    };

    template<typename Iterator, typename Comp = std::less<typename std::iterator_traits<Iterator>::value_type>>
    size_t get_inversion_count(const Iterator& first, const Iterator& last, const Comp& comp = Comp()) {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        if(first == last || first == last - 1)  return 0;
        value_type * copy_arr = new value_type[last - first];
        std::copy(first, last, copy_arr);
        size_t cnt = 0;
        get_inversion_count_(cnt, copy_arr, copy_arr + (last - first), comp);
        delete [] copy_arr;
        return cnt;
    }
}
#endif //CLRS_MERGE_SORT_HPP
