#include "sort.h"

void insertion_sort(int n, int arr[n]) {
  for (int i = 1; i < n; i++) {
    int x = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > x) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = x;
  }
}
