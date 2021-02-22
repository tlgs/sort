#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

void weak_heap_sink(int32_t arr[], int8_t r[], size_t j, size_t n) {
  size_t k = 2 * j + 1 - r[j];
  if (k >= n) {
    return;
  }

  while (2 * k + r[k] < n) {
    k = 2 * k + r[k];
  }

  while (k != j) {
    if (arr[j] < arr[k]) {
      swap(&arr[j], &arr[k]);
      r[k] = 1 - r[k];
    }
    k /= 2;
  }
}

// the weak-heap is a much less known data structure; there are
// not many (i.e. any) proper non-academic introductions to the subject.
// I recommend the papers (both by Stefan Edelkamp et. al):
//   - "The Weak-Heap Data Structure: Variants and Applications"
//   - "A Catalogue of Algorithms for Building Weak Heaps"
//
// uses the "sift-down" approach of building the weak heap
void weak_heap_sort(size_t n, int32_t arr[n]) {
  int8_t *r = calloc(n, sizeof(int8_t));

  size_t i = n < 2 ? 0 : n / 2 - 1;
  for (i++; i > 0; i--) {
    weak_heap_sink(arr, r, i - 1, n);
  }

  for (i = 1; i < n; i++) {
    swap(&arr[0], &arr[n - i]);
    weak_heap_sink(arr, r, 0, n - i);
  }
}
