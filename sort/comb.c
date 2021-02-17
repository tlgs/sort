#include <stdbool.h>
#include <stdint.h>

#include "sort.h"

#define K 1.3

void comb_sort(size_t n, int32_t arr[n]) {
  size_t gap = n;
  bool swapped;
  do {
    gap /= K;
    if (gap < 1) {
      gap = 1;
    }

    swapped = false;
    for (size_t i = gap; i < n; i++) {
      if (arr[i - gap] > arr[i]) {
        swap(&arr[i], &arr[i - gap]);
        swapped = true;
      }
    }
  } while (gap > 1 || swapped);
}
