#include <stdbool.h>
#include <stdint.h>

#include "sort.h"

void odd_even_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  bool swapped;
  do {
    swapped = false;
    for (size_t i = 1; i < n - 1; i += 2) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        swapped = true;
      }
    }
    for (size_t i = 0; i < n - 1; i += 2) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        swapped = true;
      }
    }
  } while (swapped);
}
