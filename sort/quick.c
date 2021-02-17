#include <stdint.h>

#include "sort.h"

// uses Hoare's partitioning scheme;
// uses the "median-of-three" choice of pivot (and edge ordering);
int partition(int32_t arr[], size_t lo, size_t hi) {
  size_t mid = lo + (hi - lo) / 2;
  if (arr[mid] < arr[lo]) {
    swap(&arr[mid], &arr[lo]);
  }
  if (arr[hi] < arr[lo]) {
    swap(&arr[hi], &arr[lo]);
  }
  if (arr[hi] < arr[mid]) {
    swap(&arr[hi], &arr[mid]);
  }
  int32_t pivot = arr[mid];

  size_t i = lo - 1;
  size_t j = hi + 1;
  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j) {
      return j;
    }
    swap(&arr[i], &arr[j]);
  }
}

void qs(int32_t arr[], size_t lo, size_t hi) {
  if (lo >= hi) {
    return;
  }

  size_t p = partition(arr, lo, hi);
  qs(arr, lo, p);
  qs(arr, p + 1, hi);
}

void quick_sort(size_t n, int32_t arr[n]) { qs(arr, 0, n - 1); }
