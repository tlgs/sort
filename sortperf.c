// Sort performance test; adapted from CPython's Lib/test/sortperf.py
// Array values are in the range [- RAND_MAX / 2, RAND_MAX / 2]
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort/sort.h"

// skeeto's simplified PCG
// see: <https://nullprogram.com/blog/2017/09/21/>
uint32_t spcg32(uint64_t s[1]) {
  uint64_t m = 0x9b60933458e17d7d;
  uint64_t a = 0xd737232eeccdf7ed;
  *s = *s * m + a;
  int shift = 29 - (*s >> 61);
  return *s >> shift;
}

typedef void sort_func(size_t n, int32_t arr[n]);

void do_it(int n, int arr[n], sort_func *f) {
  clock_t begin = clock();
  f(n, arr);
  clock_t end = clock();
  printf("%6.2f ", (double)(end - begin) / CLOCKS_PER_SEC);
}

int main(void) {
  uint64_t rng[] = {0x9e8480dd162324e1};
  *rng ^= time(0);

  struct {
    char *name;
    sort_func *f;
  } algo[] = {
      // {.name = "bubble sort", .f = bubble_sort},
      // {.name = "cocktail sort", .f = cocktail_sort},
      {.name = "comb sort", .f = comb_sort},
      // {.name = "cycle sort", .f = cycle_sort},
      {.name = "flashsort", .f = flash_sort},
      // {.name = "gnome sort", .f = gnome_sort},
      {.name = "heapsort", .f = heap_sort},
      // {.name = "insertion sort", .f = insertion_sort},
      {.name = "introsort", .f = intro_sort},
      {.name = "merge sort", .f = merge_sort},
      {.name = "MSD radix sort", .f = msd_radix_sort},
      // {.name = "odd-even sort", .f = odd_even_sort},
      {.name = "quicksort", .f = quick_sort},
      // {.name = "selection sort", .f = selection_sort},
      {.name = "shellsort", .f = shell_sort},
      // {.name = "stooge sort", .f = stooge_sort},
      // {.name = "strand sort", .f = strand_sort},
      {.name = "weak-heap sort", .f = weak_heap_sort},
  };

  const char header[] = " i     2**i  *sort  \\sort  /sort  3sort  +sort  "
                        "%sort  ~sort  =sort  !sort";
  for (int op = 0; op < 9; op++) {
    puts(algo[op].name);
    puts(header);

    for (int i = 15; i <= 20; i++) {
      int n = (1 << i);
      printf("%2d %8d ", i, n);

      int32_t *arr = malloc(sizeof(int32_t) * n);
      if (!arr) {
        printf("error: memory allocation");
        return EXIT_FAILURE;
      }

      // *sort
      for (int j = 0; j < n; j++) {
        arr[j] = spcg32(rng);
      }
      do_it(n, arr, algo[op].f);

      // \sort
      for (int j = 0; j < n / 2; j++) {
        swap(&arr[j], &arr[n - j - 1]);
      }
      do_it(n, arr, algo[op].f);

      // /sort
      do_it(n, arr, algo[op].f);

      // 3sort
      for (int j = 0; j < 3; j++) {
        uint64_t idx_a = spcg32(rng) % n;
        uint64_t idx_b = spcg32(rng) % n;
        swap(&arr[idx_a], &arr[idx_b]);
      }
      do_it(n, arr, algo[op].f);

      // +sort
      for (int j = n - 10; j < n; j++) {
        arr[j] = spcg32(rng);
      }
      do_it(n, arr, algo[op].f);

      // %sort
      for (int j = 0; j < n / 100; j++) {
        uint64_t idx = spcg32(rng) % n;
        arr[idx] = spcg32(rng);
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
