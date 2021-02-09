#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort.h"

#define ARR_SIZE 32000

typedef void sort_func(int n, int arr[n]);

struct sort_algo {
  char *name;
  sort_func *f;
};

int compare_int(void const *a, void const *b) {
  int const *A = a;
  int const *B = b;
  return (*A > *B) - (*A < *B);
}

int check(int sorted[ARR_SIZE], int arr[ARR_SIZE]) {
  for (int i = 0; i < ARR_SIZE; i++) {
    if (arr[i] != sorted[i]) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  srand(time(NULL));

  int r[ARR_SIZE] = {0};
  int s[ARR_SIZE] = {0};
  for (int i = 0; i < ARR_SIZE; i++) {
    r[i] = rand();
    s[i] = r[i];
  }
  qsort(s, ARR_SIZE, sizeof(int), compare_int);

  int a[ARR_SIZE] = {0};
  struct sort_algo algo[] = {
      [0] = {.name = "bubble", .f = bubble_sort},
      [1] = {.name = "insertion", .f = insertion_sort},
      [2] = {.name = "merge", .f = merge_sort},
      [3] = {.name = "quick", .f = quick_sort},
      [4] = {.name = "selection", .f = selection_sort},
      [5] = {.name = "shell", .f = shell_sort},
  };

  bool has_failed = false;
  for (int i = 0; i < SORT_ALG_N; i++) {
    memcpy(a, r, sizeof(int) * ARR_SIZE);

    algo[i].f(ARR_SIZE, a);

    char res[5];
    if (check(s, a)) {
      strcpy(res, "PASS");
    } else {
      has_failed = true;
      strcpy(res, "FAIL");
    }
    int spaces_n = 10 - strlen(algo[i].name);
    printf("[%d/%d] %s:%*c%s\n", i + 1, SORT_ALG_N, algo[i].name, spaces_n, ' ',
           res);
  }

  return has_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
