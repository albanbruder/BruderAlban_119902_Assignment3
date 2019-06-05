#ifndef BUW_BUBBLESORT_HPP
#define BUW_BUBBLESORT_HPP

#include <functional>

template <typename Iterator, typename Comp>
void bubblesort(Iterator first, Iterator last, Comp comp)
{
  for(auto i = first; i != last; ++i) {
    for(auto j = first; j < i; ++j) {
      if(comp(*i, *j)) {
        std::iter_swap(i, j);
      }
    }
  }
};

template <typename Iterator>
void bubblesort(Iterator first, Iterator last)
{
  auto comp = std::less<typename Iterator::value_type>();
  for(auto i = first; i != last; ++i) {
    for(auto j = first; j < i; ++j) {
      if(comp(*i, *j)) {
        std::iter_swap(i, j);
      }
    }
  }
};

#endif