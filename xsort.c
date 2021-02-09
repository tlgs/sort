// about the vector reallocation growth factor:
// https://github.com/facebook/folly/blob/master/folly/docs/FBVector.md#memory-handling
#include <io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define INIT_CAP 1000
#define K 1.5

typedef void sort_func(int n, int arr[n]);

struct sort_algo {
  char *option;
  sort_func *f;
};

void print_help(void) { puts("help"); }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("you should probably run `xsort --help`");
    return EXIT_FAILURE;
  }

  if ((strcmp(argv[1], "--help") * strcmp(argv[1], "-h")) == 0) {
    print_help();
    return EXIT_SUCCESS;
  }

  struct sort_algo algo[] = {
      [0] = {.option = "--bubble", .f = bubble_sort},
      [1] = {.option = "--insertion", .f = insertion_sort},
      [2] = {.option = "--merge", .f = merge_sort},
      [3] = {.option = "--quick", .f = quick_sort},
      [4] = {.option = "--selection", .f = selection_sort},
      [5] = {.option = "--shell", .f = shell_sort},
  };

  int op = 0;
  while (op < SORT_ALG_N && (strcmp(argv[1], algo[op].option) != 0)) {
    op++;
  }

  if (op >= SORT_ALG_N) {
    printf("unknown option: %s\n", argv[1]);
    puts("see `xsort --help` for available options");
    return EXIT_FAILURE;
  }

  bool const tty = _isatty(_fileno(stdin)); // windows specific
  if (tty && argc < 3) {
    puts("error: missing file");
    return EXIT_FAILURE;
  } else if (!tty && argc > 2) {
    puts("error: too many arguments for this mode");
    return EXIT_FAILURE;
  }

  int n = 0;
  int cap = INIT_CAP;
  int *arr = malloc(sizeof(int) * cap);
  if (!arr) {
    puts("error: memory allocation");
    return EXIT_FAILURE;
  }

  FILE *fp;
  if (tty) {
    fp = fopen(argv[2], "r");
    if (!fp) {
      puts("error: opening file");
      return EXIT_FAILURE;
    }
  }

  int x;
  while (true) {
    if (tty) {
      if (fscanf(fp, "%d", &x) != 1) {
        fclose(fp);
        break;
      }
    } else {
      if (scanf("%d", &x) != 1) {
        break;
      }
    }

    if (n + 1 > cap) {
      cap *= K;
      arr = realloc(arr, sizeof(int) * cap);
      if (!arr) {
        puts("error: memory re-allocation");
        return EXIT_FAILURE;
      }
    }
    arr[n] = x;
    n++;
  }

  algo[op].f(n, arr);
  for (int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }

  free(arr);
  return EXIT_SUCCESS;
}
