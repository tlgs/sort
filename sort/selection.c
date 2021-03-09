#include <stdint.h>

#include "sort.h"

void selection_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  for (size_t i = 0; i < n - 1; i++) {
    size_t min_idx = i;
    for (size_t j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    swap(&arr[i], &arr[min_idx]);
  }
}
