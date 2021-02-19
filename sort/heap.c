#include <stdint.h>

#include "sort.h"

void sift_down(int32_t arr[], size_t start, size_t end) {
  size_t root = start;
  while (root * 2 + 1 < end) {
    size_t child = root * 2 + 1;
    if (child + 1 < end && arr[child] < arr[child + 1]) {
      child++;
    }

    if (arr[root] < arr[child]) {
      swap(&arr[root], &arr[child]);
      root = child;
    } else {
      return;
    }
  }
}

void heapify(int32_t arr[], size_t n) {
  if (n < 3) {
    return;
  }

  size_t i = (n - 2) / 2;
  while (i > 0) {
    sift_down(arr, i, n);
    i--;
  }
  sift_down(arr, 0, n);
}

void heap_sort(size_t n, int32_t arr[n]) {
  heapify(arr, n);

  size_t i = n - 1;
  while (i > 0) {
    swap(&arr[i], &arr[0]);
    sift_down(arr, 0, i);
    i--;
  }
}
