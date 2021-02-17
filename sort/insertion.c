#include <stdint.h>

#include "sort.h"

void insertion_sort(size_t n, int32_t arr[n]) {
  for (size_t i = 1; i < n; i++) {
    int32_t x = arr[i];
    size_t j = i;
    while (j > 0 && arr[j - 1] > x) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = x;
  }
}
