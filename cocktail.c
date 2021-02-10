#include "sort.h"

// includes the "last swap" optimization which shrinks the comparison space
void cocktail_sort(int n, int arr[n]) {
  int start = 0;
  do {
    int last_swap = start;
    for (int i = start + 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        int tmp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = tmp;

        last_swap = i;
      }
    }
    n = last_swap;

    for (int i = n - 2; i > start - 1; i--) {
      if (arr[i + 1] < arr[i]) {
        int tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;

        last_swap = i;
      }
    }
    start = last_swap + 1;

  } while (n > start);
}