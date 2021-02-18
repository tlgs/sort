#include <stdint.h>
#include <stdio.h>

#include "sort.h"

void ss(int32_t arr[], size_t lo, size_t hi) {
  if (arr[lo] > arr[hi - 1]) {
    swap(&arr[lo], &arr[hi - 1]);
  }

  if (hi - lo > 2) {
    size_t t = (hi - lo) / 3;
    ss(arr, lo, hi - t);
    ss(arr, lo + t, hi);
    ss(arr, lo, hi - t);
  }
}

void stooge_sort(size_t n, int32_t arr[n]) { ss(arr, 0, n); }
