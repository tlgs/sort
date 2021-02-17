#include "sort.h"

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// uses Hoare's partitioning scheme;
// uses the "median-of-three" choice of pivot (and edge ordering);
int partition(int arr[], int lo, int hi) {
  int mid = lo + (hi - lo) / 2;
  if (arr[mid] < arr[lo]) {
    swap(&arr[mid], &arr[lo]);
  }
  if (arr[hi] < arr[lo]) {
    swap(&arr[hi], &arr[lo]);
  }
  if (arr[hi] < arr[mid]) {
    swap(&arr[hi], &arr[mid]);
  }
  int pivot = arr[mid];

  int i = lo - 1;
  int j = hi + 1;
  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j) {
      return j;
    }
    swap(&arr[i], &arr[j]);
  }
}

void qs(int arr[], int lo, int hi) {
  if (lo >= hi) {
    return;
  }

  int p = partition(arr, lo, hi);
  qs(arr, lo, p);
  qs(arr, p + 1, hi);
}

void quick_sort(int n, int arr[n]) { qs(arr, 0, n - 1); }
