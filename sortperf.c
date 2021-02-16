// Sort performance test.
// Adapted from CPython's Lib/test/sortperf.py
//
// Key:
//   *sort: random data
//   \sort: descending data
//   /sort: ascending data
//   3sort: ascending, then 3 random exchanges
//   +sort: ascending, then 10 random at the end
//   %sort: ascending, then randomly replace 1% of the elements w/ random values
//   ~sort: many duplicates
//   =sort: all equal
//   !sort: worst case scenario
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort.h"

typedef void sort_func(int n, int arr[n]);

void do_it(int n, int arr[n], sort_func *f) {
  clock_t begin = clock();
  f(n, arr);
  clock_t end = clock();
  printf("%6.2f ", (double)(end - begin) / CLOCKS_PER_SEC);
}

// rand() only returns a number up to RAND_MAX (which is only guaranteed to be
// at least 32767).
// A simple way to obtain higher numbers is to sum up multiple rand() calls.
// If we want our upper bound to be *n*,
// we call it (n / RAND_MAX) + 1 times.
int rand_bigger(int n) {
  int k = (n / RAND_MAX) + 1;
  int r = 0;
  for (int i = 0; i < k; i++) {
    r += rand();
  }
  return r % (n + 1);
}

int main(void) {
  srand(time(NULL));

  struct sort_algo {
    char *name;
    sort_func *f;
    int iters;
  } algo[] = {
      {.name = "comb sort", .f = comb_sort},
      {.name = "merge sort", .f = merge_sort},
      {.name = "quicksort", .f = quick_sort},
      {.name = "shellsort", .f = shell_sort},
  };

  for (int op = 0; op < 4; op++) {
    puts(algo[op].name);
    printf("%2s %8s  *sort  \\sort  /sort  3sort  +sort  %%sort  ~sort  =sort  "
           "!sort\n",
           "i", "2**i");

    for (int i = 15; i <= 20; i++) {
      int n = (1 << i);
      printf("%2d %8d ", i, n);

      int *arr = malloc(sizeof(int) * n);
      if (!arr) {
        printf("error: memory allocation");
        return EXIT_FAILURE;
      }

      // *sort
      for (int j = 0; j < n; j++) {
        arr[j] = rand();
      }
      do_it(n, arr, algo[op].f);

      // \sort
      for (int j = 0; j < n / 2; j++) {
        int tmp = arr[j];
        arr[j] = arr[n - j - 1];
        arr[n - j - 1] = tmp;
      }
      do_it(n, arr, algo[op].f);

      // /sort
      do_it(n, arr, algo[op].f);

      // 3sort
      for (int j = 0; j < 3; j++) {
        int idx_a = rand_bigger(n);
        int idx_b = rand_bigger(n);
        int tmp = arr[idx_a];
        arr[idx_a] = arr[idx_b];
        arr[idx_b] = tmp;
      }
      do_it(n, arr, algo[op].f);

      // +sort
      for (int j = n - 10; j < n; j++) {
        arr[j] = rand();
      }
      do_it(n, arr, algo[op].f);

      // %sort
      for (int j = 0; j < n / 100; j++) {
        int idx = rand_bigger(n);
        arr[idx] = rand();
      }
      do_it(n, arr, algo[op].f);

      // ~sort
      for (int j = 4; j < n; j += 4) {
        arr[j] = arr[0];
        arr[j + 1] = arr[1];
        arr[j + 2] = arr[2];
        arr[j + 3] = arr[3];
      }
      do_it(n, arr, algo[op].f);

      // =sort
      for (int j = 0; j < n; j++) {
        arr[j] = 42;
      }
      do_it(n, arr, algo[op].f);

      // !sort
      int half = n / 2;
      for (int j = 0; j < half; j++) {
        arr[j] = half - 1 - j;
      }
      for (int j = 0; j < half; j++) {
        arr[half + j] = j;
      }
      do_it(n, arr, algo[op].f);
      printf("\n");

      free(arr);
    }

    printf("\n");
  }

  return EXIT_SUCCESS;
}
