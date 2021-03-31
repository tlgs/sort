#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "sort.h"

// comb sort is a variation of bubble sort that attempts to "kill turtles"
// more effectively than the cocktail sort variant.
// the idea of comparing elements a great distance apart allow for "turtles"
// to move great distances quickly; by the time the gap approaches 1, most
// "turtles" have been dealt with and bubble sort is rather efficient.
//
// the shrinking factor and prefered ending sequence (Combsort11) are determined
// empirically as described by Stepehen Lacy and Richard Box in:
// <http://cs.clackamas.cc.or.us/molatore/cs260Spr03/combsort.htm>
void comb_sort(size_t n, int32_t arr[n]) {
  size_t gap = n;
  bool swapped;
  do {
    gap /= 1.3;
    if (gap == 9 || gap == 10) {
      gap = 11;
    } else if (gap < 1) {
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
