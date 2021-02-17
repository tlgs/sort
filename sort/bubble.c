#include <stdint.h>

#include "sort.h"

// uses the "last swap" optimization to reduce comparison count
void bubble_sort(size_t n, int32_t arr[n]) {
  do {
    size_t last_swap = 0;
    for (size_t i = 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        swap(&arr[i], &arr[i - 1]);
        last_swap = i;
      }
    }
    n = last_swap;
  } while (n > 1);
}
