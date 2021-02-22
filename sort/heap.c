#include <stdint.h>

#include "sort.h"

void heap_sink(int32_t arr[], size_t i, size_t n) {
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
  heap_sink(arr, child, n);
}

void heap_sort(size_t n, int32_t arr[n]) {
  size_t i = n < 2 ? 0 : (n - 2) / 2;
  for (i++; i > 0; i--) {
    heap_sink(arr, i - 1, n);
  }

  for (i = 1; i < n; i++) {
    swap(&arr[0], &arr[n - i]);
    heap_sink(arr, 0, n - i);
  }
}
