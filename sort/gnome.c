#include <stdint.h>

#include "sort.h"

void gnome_sort(size_t n, int32_t arr[n]) {
  size_t i = 1;
  size_t top = 2;
  while (i < n) {
    if (i == 0 || arr[i - 1] <= arr[i]) {
      i = top++;
    } else {
      swap(&arr[i], &arr[i - 1]);
      i--;
    }
  }
}
