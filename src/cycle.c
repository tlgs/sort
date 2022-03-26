#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "sort.h"

void cycle_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  for (size_t start = 0; start < n - 1; start++) {
    bool first = true;
    size_t pos;
    int32_t x = arr[start];
    do {
      pos = start;
      for (size_t i = start + 1; i < n; i++) {
        if (arr[i] < x) {
          pos++;
        }
      }
      if (first && pos == start) {
        break;
      }
      while (arr[pos] == x) {
        pos++;
      }
      swap(&x, &arr[pos]);

      first = false;
    } while (pos != start);
  }
}
