#include <stdint.h>

#include "sort.h"

void intro_sort2(int32_t arr[], size_t lo, size_t hi, uint16_t maxdepth) {
  if (hi - lo + 1 < 20) {
    insertion_sort(hi - lo + 1, arr + lo);
  } else if (maxdepth == 0) {
    heap_sort(hi - lo + 1, arr + lo);
  } else {
    size_t p = quick_partition(arr, lo, hi);
    intro_sort2(arr, lo, p, maxdepth - 1);
    intro_sort2(arr, p + 1, hi, maxdepth - 1);
  }
}

void intro_sort(size_t n, int32_t arr[n]) {
  uint16_t depth = 0;
  for (size_t i = n; i > 1; i >>= 1) {
    depth++;
  }
  intro_sort2(arr, 0, n - 1, 2 * depth);
}
