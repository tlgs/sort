#include <stdlib.h>

#include "sort.h"

void merge(int arr[], int l, int m, int r) {
  // bad: no verification that this malloc succeeds!
  int *aux = malloc(sizeof(int) * (r - l + 1));
  for (int i = 0; i <= r - l; i++) {
    aux[i] = arr[l + i];
  }

  int i = l;
  int a = 0;
  int b = m - l + 1;
  while (a <= m - l && b <= r - l) {
    if (aux[a] < aux[b]) {
      arr[i++] = aux[a++];
    } else {
      arr[i++] = aux[b++];
    }
  }

  while (a <= m - l) {
    arr[i++] = aux[a++];
  }

  while (b <= r - l) {
    arr[i++] = aux[b++];
  }

  free(aux);
}

void ms(int arr[], int l, int r) {
  if (l >= r) {
    return;
  }

  int m = l + (r - l) / 2;
  ms(arr, l, m);
  ms(arr, m + 1, r);
  merge(arr, l, m, r);
}

void merge_sort(int n, int arr[n]) { ms(arr, 0, n - 1); }
