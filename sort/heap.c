#include <stdint.h>

#include "sort.h"

void sink(int32_t arr[], size_t i, size_t n) {
  size_t child = 2 * i + 1;
  if (child >= n) {
    return;
  }
  if (child + 1 < n && arr[child + 1] > arr[child]) {
    child++;
  }

  if (arr[i] >= arr[child]) {
    return;
  }
  swap(&arr[i], &arr[child]);
  sink(arr, child, n);
}

void heap_sort(size_t n, int32_t arr[n]) {
  if (n > 2) {
    for (size_t i = ((n - 2) / 2) + 1; i > 0; i--) {
      sink(arr, i - 1, n);
    }
  }

  for (size_t i = 1; i < n; i++) {
    swap(&arr[0], &arr[n - i]);
    sink(arr, 0, n - i);
  }
}
