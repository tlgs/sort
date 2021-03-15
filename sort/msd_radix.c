#include <stdint.h>

#include "sort.h"

// helper uint32_t insertion sort when threshold is reached
void msd_radix_isort(size_t n, uint32_t arr[n]) {
  for (size_t i = 1; i < n; i++) {
    uint32_t x = arr[i];
    size_t j = i;
    while (j > 0 && arr[j - 1] > x) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = x;
  }
}

void msd_radix_sort2(uint32_t arr[], size_t lo, size_t hi, int8_t shift) {
  if (shift < 0 || lo >= hi) {
    return;
  }

  size_t last[256] = {[0] = lo};
  for (size_t i = lo; i < hi; i++) {
    last[(arr[i] >> shift) & 0xFF]++;
  }

  size_t curr[256] = {[0] = lo};
  for (size_t i = 1; i < 256; i++) {
    last[i] += last[i - 1];
    curr[i] = last[i - 1];
  }

  for (size_t i = 0; i < 256; i++) {
    while (curr[i] != last[i]) {
      uint32_t value = arr[curr[i]];
      size_t j = (value >> shift) & 0xFF;
      while (j != i) {
        uint32_t tmp = arr[curr[j]];
        arr[curr[j]] = value;
        value = tmp;

        curr[j]++;

        j = (value >> shift) & 0xFF;
      }
      arr[curr[i]] = value;
      curr[i]++;
    }
  }

  for (size_t i = 0; i < 256; i++) {
    size_t new_lo = i ? curr[i - 1] : lo;
    if (curr[i] - new_lo < 64) {
      msd_radix_isort(curr[i] - new_lo, arr + new_lo);
    } else {
      msd_radix_sort2(arr, new_lo, curr[i], shift - 8);
    }
  }
}

void msd_radix_sort(size_t n, int32_t arr[n]) {
  uint32_t *x = (uint32_t *)arr;

  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }

  msd_radix_sort2(x, 0, n, 32 - 8);

  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }
}
