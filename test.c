#include <stdbool.h>
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

int compare_int(void const *a, void const *b) {
  int const *A = a;
  int const *B = b;
  return (*A > *B) - (*A < *B);
}

bool is_sorted(int n, int32_t sorted[n], int32_t arr[n]) {
  for (int i = 0; i < n; i++) {
    if (arr[i] != sorted[i]) {
      return false;
    }
  }
  return true;
}

int main(void) {
  uint64_t rng[] = {0x9e8480dd162324e1};
  *rng ^= time(0);

  typedef void sort_func(size_t n, int32_t arr[n]);
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

  int const arr_size[] = {0, 1, 2, 3, 42, 99, 100, 1337};

  bool any_failed = false;
  for (int i = 0; i < SORT_ALG_N; i++) {
    bool failed = false;
    int runs = sizeof(arr_size) / sizeof(arr_size[0]);
    for (int j = 0; j < runs && !failed; j++) {
      int n = arr_size[j];

      int32_t *r = malloc(sizeof(int32_t) * n);
      if (!r) {
        return EXIT_FAILURE;
      }
      int32_t *s = malloc(sizeof(int32_t) * n);
      if (!s) {
        return EXIT_FAILURE;
      }
      for (int k = 0; k < n; k++) {
        r[k] = spcg32(rng);
        s[k] = r[k];
      }
      qsort(s, n, sizeof(int32_t), compare_int);

      int32_t *a = malloc(sizeof(int32_t) * n);
      if (!a) {
        return EXIT_FAILURE;
      }
      memcpy(a, r, sizeof(int32_t) * n);
      algo[i].f(n, a);
      failed = !is_sorted(n, s, a);

      free(r);
      free(s);
      free(a);
    }
    any_failed = (any_failed || failed);

    char res[2][5] = {"PASS", "FAIL"};
    int spaces = 10 - strlen(algo[i].name);
    printf("[%2d/%d] %s:%*c%s\n", i + 1, SORT_ALG_N, algo[i].name, spaces, ' ',
           res[failed]);
  }

  return any_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
