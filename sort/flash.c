#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

// see: https://www.drdobbs.com/database/the-flashsort1-algorithm/184410496
void flash_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  int32_t min = arr[0];
  int32_t max = arr[0];
  for (size_t i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    } else if (arr[i] < min) {
      min = arr[i];
    }
  }

  size_t m = 0.1 * n;
  if (m < 1) {
    m = 1;
  }
  size_t range = ((size_t)max - min) / m + 1;
  size_t *bucket = calloc(m, sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    size_t b = ((size_t)arr[i] - min) / range;
    bucket[b]++;
  }

  for (size_t i = 1; i < m; i++) {
    bucket[i] += bucket[i - 1];
  }

  for (size_t i = 0; i < n - 1; i++) {
    size_t b = ((size_t)arr[i] - min) / range;
    if (i < bucket[b]) {
      size_t j;
      do {
        j = bucket[b] - 1;
        swap(&arr[i], &arr[j]);
        bucket[b]--;
        b = ((size_t)arr[i] - min) / range;
      } while (j != i);
    }
  }
  free(bucket);

  // performing insertion sort on each individual bucket is
  // equivalent to running it over the whole array
  insertion_sort(n, arr);
}
