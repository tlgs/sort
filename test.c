#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort.h"

int compare_int(void const *a, void const *b) {
  int const *A = a;
  int const *B = b;
  return (*A > *B) - (*A < *B);
}

bool is_sorted(int n, int sorted[n], int arr[n]) {
  for (int i = 0; i < n; i++) {
    if (arr[i] != sorted[i]) {
      return false;
    }
  }
  return true;
}

int main(void) {
  srand(time(NULL));

  typedef void sort_func(int n, int arr[n]);
  struct sort_algo {
    char *name;
    sort_func *f;
  } algo[] = {
      {.name = "bubble", .f = bubble_sort},
      {.name = "cocktail", .f = cocktail_sort},
      {.name = "comb", .f = comb_sort},
      {.name = "insertion", .f = insertion_sort},
      {.name = "merge", .f = merge_sort},
      {.name = "quick", .f = quick_sort},
      {.name = "selection", .f = selection_sort},
      {.name = "shell", .f = shell_sort},
  };

  int const arr_size[] = {1, 2, 42, 99, 100, 1337, 9999};

  bool any_failed = false;
  for (int i = 0; i < SORT_ALG_N; i++) {
    bool failed = false;
    int runs = sizeof(arr_size) / sizeof(arr_size[0]);
    for (int j = 0; j < runs && !failed; j++) {
      int n = arr_size[j];

      int *r = malloc(sizeof(int) * n);
      if (!r) {
        return EXIT_FAILURE;
      }
      int *s = malloc(sizeof(int) * n);
      if (!s) {
        return EXIT_FAILURE;
      }
      for (int k = 0; k < n; k++) {
        r[k] = rand();
        s[k] = r[k];
      }
      qsort(s, n, sizeof(int), compare_int);

      int *a = malloc(sizeof(int) * n);
      if (!a) {
        return EXIT_FAILURE;
      }
      memcpy(a, r, sizeof(int) * n);
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
    printf("[%d/%d] %s:%*c%s\n", i + 1, SORT_ALG_N, algo[i].name, spaces_n, ' ',
           res);
  }

  return any_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
