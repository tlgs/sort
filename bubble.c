#include "sort.h"

// includes the "last swap" optimization which shrinks the comparison space
void bubble_sort(int n, int arr[n]) {
  do {
    int last_swap = 0;
    for (int i = 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        int tmp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = tmp;

        last_swap = i;
      }
    }
    n = last_swap;
  } while (n > 1);
}
