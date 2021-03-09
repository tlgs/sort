#include <stdint.h>
#include <stdio.h>

#include "sort.h"

void stooge_sort2(int32_t arr[], size_t lo, size_t hi) {
  if (arr[lo] > arr[hi - 1]) {
    swap(&arr[lo], &arr[hi - 1]);
  }

  if (hi - lo > 2) {
    size_t t = (hi - lo) / 3;
    stooge_sort2(arr, lo, hi - t);
    stooge_sort2(arr, lo + t, hi);
    stooge_sort2(arr, lo, hi - t);
  }
}

void stooge_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  stooge_sort2(arr, 0, n);
}
