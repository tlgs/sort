#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define INIT_CAP 1024
#define K 1.5

typedef void sort_func(int n, int arr[n]);

struct sort_algo {
  char *option;
  sort_func *f;
};

void print_help(void) {
  puts("xsort 0.1.0, a study of sorting algorithms");
  puts("Sort lines of integers");
  puts("");
  puts("Usage:");
  puts("  xsort --bubble [FILE]");
  puts("  xsort --cocktail [FILE]");
  puts("  xsort --comb [FILE]");
  puts("  xsort --insertion [FILE]");
  puts("  xsort --merge [FILE]");
  puts("  xsort --quick [FILE]");
  puts("  xsort --selection [FILE]");
  puts("  xsort --shell [FILE]");
  puts("");
  puts("Description:");
  puts("  Write sorted integers to stdout.");
  puts("  With no FILE, read from stdin.");
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    puts("you should probably run `xsort --help`");
    return EXIT_FAILURE;
  }

  if ((strcmp(argv[1], "--help") * strcmp(argv[1], "-h")) == 0) {
    print_help();
    return EXIT_SUCCESS;
  }

  struct sort_algo algo[] = {
      {.option = "--bubble", .f = bubble_sort},
      {.option = "--cocktail", .f = cocktail_sort},
      {.option = "--comb", .f = comb_sort},
      {.option = "--insertion", .f = insertion_sort},
      {.option = "--merge", .f = merge_sort},
      {.option = "--quick", .f = quick_sort},
      {.option = "--selection", .f = selection_sort},
      {.option = "--shell", .f = shell_sort},
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

  bool const tty = (argc == 3);

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
