#include <stdbool.h>

#include "sort.h"

void bubble_sort(int n, int arr[n]) {
  int i = 0;
  bool swapped;
  do {
    swapped = false;
    for (int j = 1; j < n - i; j++) {
      if (arr[j - 1] > arr[j]) {
        int tmp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = tmp;

        swapped = true;
      }
    }
    i++;
  } while (swapped);
}
