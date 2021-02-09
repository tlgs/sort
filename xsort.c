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

void print_help(void) { puts("help"); }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("you should probably run `xsort --help`");
    return EXIT_FAILURE;
  }

  // TODO: unify options with the sorting functions
  char const *options[] = {
      [0] = "--help",  [1] = "--bubble", [2] = "--insertion",
      [3] = "--merge", [4] = "--quick",  [5] = "--selection",
      [6] = "--shell",
  };
  int op = 0;
  bool valid = false;
  for (; op < 7; op++) {
    if (strcmp(argv[1], options[op]) == 0) {
      valid = true;
      break;
    }
  }

  if (!valid) {
    printf("unknown option: %s\n", argv[1]);
    puts("see `xsort --help` for available options");
    return EXIT_FAILURE;
  }

  bool const is_help = (op == 0);
  if (is_help) {
    print_help();
    return EXIT_SUCCESS;
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

  typedef void sort_func(int n, int arr[n]);
  sort_func *algo[] = {
      [0] = bubble_sort, [1] = insertion_sort, [2] = merge_sort,
      [3] = quick_sort,  [4] = selection_sort, [5] = shell_sort,
  };
  algo[op - 1](n, arr);
  for (int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }

  free(arr);
  return EXIT_SUCCESS;
}
