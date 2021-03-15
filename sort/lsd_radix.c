#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

void lsd_radix_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  uint32_t *x = (uint32_t *)arr;
  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }

  uint32_t *aux = malloc(sizeof(uint32_t) * n);
  for (int32_t shift = 0; shift < 32; shift += 8) {
    size_t count[256] = {0};
    for (size_t i = 0; i < n; i++) {
      count[(x[i] >> shift) & 0xFF]++;
    }
    for (size_t i = 1; i < 256; i++) {
      count[i] += count[i - 1];
    }
    for (size_t i = n; i > 0; i--) {
      size_t bin = (x[i - 1] >> shift) & 0xFF;
      count[bin]--;
      aux[count[bin]] = x[i - 1];
    }
    for (size_t i = 0; i < n; i++) {
      x[i] = aux[i];
    }
  }
  free(aux);

  for (size_t i = 0; i < n; i++) {
    x[i] ^= (1 << 31);
  }
}
