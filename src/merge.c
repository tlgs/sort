#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

void merge(int32_t arr[], int32_t aux[], size_t l, size_t m, size_t r) {
  for (size_t i = 0; i <= r - l; i++) {
    aux[i] = arr[l + i];
  }

  size_t i = l;
  size_t a = 0;
  size_t b = m - l + 1;
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
}

void merge_sort2(int32_t arr[], int32_t aux[], size_t l, size_t r) {
  if (l >= r) {
    return;
  }

  size_t m = l + (r - l) / 2;
  merge_sort2(arr, aux, l, m);
  merge_sort2(arr, aux, m + 1, r);
  merge(arr, aux, l, m, r);
}

void merge_sort(size_t n, int32_t arr[n]) {
  if (n == 0) {
    return;
  }

  int32_t *aux = malloc(sizeof(int32_t) * n);
  merge_sort2(arr, aux, 0, n - 1);
  free(aux);
}
