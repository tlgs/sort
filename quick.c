#include "sort.h"

int partition(int arr[], int lo, int hi) {
  int pivot = arr[hi];
  int i = lo;
  for (int j = lo; j < hi; j++) {
    if (arr[j] < pivot) {
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
    }
  }
  arr[hi] = arr[i];
  arr[i] = pivot;

  return i;
}

void qs(int arr[], int lo, int hi) {
  if (lo >= hi) {
    return;
  }

  int p = partition(arr, lo, hi);
  qs(arr, lo, p - 1);
  qs(arr, p + 1, hi);
}

void quick_sort(int n, int arr[n]) { qs(arr, 0, n - 1); }
