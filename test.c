#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort/sort.h"

typedef void sort_func(size_t n, int32_t arr[n]);

bool is_sorted(int n, int32_t arr[n]) {
  int32_t prev = INT32_MIN;
  for (int i = 0; i < n; i++) {
    if (arr[i] < prev) {
      return false;
    }
    prev = arr[i];
  }
  return true;
}

// skeeto's simplified PCG
// <https://nullprogram.com/blog/2017/09/21/>
uint32_t spcg32(uint64_t s[1]) {
  uint64_t m = 0x9b60933458e17d7d;
  uint64_t a = 0xd737232eeccdf7ed;
  *s = *s * m + a;
  int shift = 29 - (*s >> 61);
  return *s >> shift;
}

int main(void) {
  uint64_t rng[] = {0x9e8480dd162324e1};
  *rng ^= time(0);

  struct {
    char *name;
    sort_func *f;
  } algo[] = {
      {.name = "bubble", .f = bubble_sort},
      {.name = "cocktail", .f = cocktail_sort},
      {.name = "comb", .f = comb_sort},
      {.name = "cycle", .f = cycle_sort},
      {.name = "flash", .f = flash_sort},
      {.name = "gnome", .f = gnome_sort},
      {.name = "heap", .f = heap_sort},
      {.name = "insertion", .f = insertion_sort},
      {.name = "intro", .f = intro_sort},
      {.name = "lsd-radix", .f = lsd_radix_sort},
      {.name = "merge", .f = merge_sort},
      {.name = "msd-radix", .f = msd_radix_sort},
      {.name = "odd-even", .f = odd_even_sort},
      {.name = "quick", .f = quick_sort},
      {.name = "selection", .f = selection_sort},
      {.name = "shell", .f = shell_sort},
      {.name = "stooge", .f = stooge_sort},
      {.name = "strand", .f = strand_sort},
      {.name = "weak-heap", .f = weak_heap_sort},
  };

  int32_t arr[1337] = {0};
  int const arr_size[] = {0, 1, 2, 3, 42, 99, 100, 1337};

  bool any_failed = false;
  for (int i = 0; i < SORT_ALG_N; i++) {
    bool failed = false;
    int runs = sizeof(arr_size) / sizeof(arr_size[0]);
    for (int j = 0; j < runs && !failed; j++) {
      int n = arr_size[j];

      for (int k = 0; k < n; k++) {
        arr[k] = spcg32(rng);
      }

      algo[i].f(n, arr);
      failed = !is_sorted(n, arr);
    }

    char res[2][5] = {"PASS", "FAIL"};
    printf("[%2d/%d] %-9s %s\n", i + 1, SORT_ALG_N, algo[i].name, res[failed]);

    any_failed = (any_failed || failed);
  }

  return any_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
