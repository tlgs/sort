#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort/sort.h"

typedef void sort_func(size_t n, int32_t arr[n]);

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
  srand(time(0));

  struct sort_algo {
    char *name;
    sort_func *f;
  } algo[] = {
      {.name = "bubble", .f = bubble_sort},
      {.name = "cocktail", .f = cocktail_sort},
      {.name = "comb", .f = comb_sort},
      {.name = "gnome", .f = gnome_sort},
      {.name = "heap", .f = heap_sort},
      {.name = "insertion", .f = insertion_sort},
      {.name = "merge", .f = merge_sort},
      {.name = "odd-even", .f = odd_even_sort},
      {.name = "quick", .f = quick_sort},
      {.name = "selection", .f = selection_sort},
      {.name = "shell", .f = shell_sort},
      {.name = "stooge", .f = stooge_sort},
  };

  int const arr_size[] = {1, 2, 3, 42, 99, 100, 1337};

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
        r[k] = rand() - RAND_MAX / 2;
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

    char res[5];
    strcpy(res, failed ? "FAIL" : "PASS");
    int spaces_n = 10 - strlen(algo[i].name);
    printf("[%2d/%d] %s:%*c%s\n", i + 1, SORT_ALG_N, algo[i].name, spaces_n,
           ' ', res);
  }

  return any_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
