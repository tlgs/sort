#include <stdint.h>
#include <stdbool.h>

#include "sort.h"

void msd_radix_sort2(uint32_t arr[], size_t lo, size_t hi, uint32_t bit) {
  if (!bit || lo >= hi) {
    return;
  }

  uint32_t left = lo;
  uint32_t right = hi - 1;
  while (true) {
    while (left < right && !(arr[left] & bit)) {
      left++;
    }
    while (left < right && (arr[right] & bit)) {
      right--;
    }
    if (left >= right) {
      break;
    }

    // uint32_t swap
    uint32_t tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
  }

  if (!(arr[left] & bit) && left < hi) {
    left++;
  }

  msd_radix_sort2(arr, lo, left, bit >> 1);
  msd_radix_sort2(arr, left, hi, bit >> 1);
}

void msd_radix_sort(size_t n, int32_t arr[n]) {
  uint32_t *x = (uint32_t *)arr;

  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }

  msd_radix_sort2(x, 0, n, 1 << 31);

  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }
}
