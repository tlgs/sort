#include <stdbool.h>

#include "sort.h"

#define K 1.3

void comb_sort(int n, int arr[n]) {
  int gap = n;
  bool swapped;
  do {
    gap /= K;
    if (gap < 1) {
      gap = 1;
    }
    
    swapped = false;
    for (int i = gap; i < n; i++) {
      if (arr[i - gap] > arr[i]) {
        int tmp = arr[i];
        arr[i] = arr[i - gap];
        arr[i - gap] = tmp;

        swapped = true;
      }
    }
  } while (gap > 1 || swapped);
}
