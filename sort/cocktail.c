#include <stdint.h>

#include "sort.h"

// cocktail sort is a variation of bubble sort that operates in both directions;
// this hopes to "kill turtles", i.e. move small elements to the beginning of
// the list.
// uses the "last swap" optimization to reduce comparison count
void cocktail_sort(size_t n, int32_t arr[n]) {
  size_t start = 0;
  do {
    size_t last_swap = start;
    for (size_t i = start + 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        swap(&arr[i], &arr[i - 1]);
        last_swap = i;
      }
    }
    n = last_swap;

    for (size_t i = n; i > start + 1; i--) {
      if (arr[i - 1] < arr[i - 2]) {
        swap(&arr[i - 2], &arr[i - 1]);
        last_swap = i - 2;
      }
    }
    start = last_swap + 1;

  } while (n > start);
}
