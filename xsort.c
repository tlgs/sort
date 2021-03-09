#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort/sort.h"

#define INIT_CAP 1024
#define K 1.5

void print_help(void) {
  puts("xsort 0.1.0, a study of sorting algorithms");
  puts("Usage:");
  puts("  xsort --bubble [FILE]");
  puts("  xsort --cocktail [FILE]");
  puts("  xsort --comb [FILE]");
  puts("  xsort --cycle [FILE]");
  puts("  xsort --flash [FILE]");
  puts("  xsort --gnome [FILE]");
  puts("  xsort --heap [FILE]");
  puts("  xsort --insertion [FILE]");
  puts("  xsort --intro [FILE]");
  puts("  xsort --merge [FILE]");
  puts("  xsort --odd-even [FILE]");
  puts("  xsort --quick [FILE]");
  puts("  xsort --selection [FILE]");
  puts("  xsort --shell [FILE]");
  puts("  xsort --stooge [FILE]");
  puts("  xsort --strand [FILE]");
  puts("  xsort --weak-heap [FILE]");
  puts("  xsort -h | --help");
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

  typedef void sort_func(size_t n, int32_t arr[n]);
  struct {
    char *option;
    sort_func *f;
  } algo[] = {
      {.option = "--bubble", .f = bubble_sort},
      {.option = "--cocktail", .f = cocktail_sort},
      {.option = "--comb", .f = comb_sort},
      {.option = "--cycle", .f = cycle_sort},
      {.option = "--flash", .f = flash_sort},
      {.option = "--gnome", .f = gnome_sort},
      {.option = "--heap", .f = heap_sort},
      {.option = "--insertion", .f = insertion_sort},
      {.option = "--intro", .f = intro_sort},
      {.option = "--merge", .f = merge_sort},
      {.option = "--odd-even", .f = odd_even_sort},
      {.option = "--quick", .f = quick_sort},
      {.option = "--selection", .f = selection_sort},
      {.option = "--shell", .f = shell_sort},
      {.option = "--stooge", .f = stooge_sort},
      {.option = "--strand", .f = strand_sort},
      {.option = "--weak-heap", .f = weak_heap_sort},
  };

  int op = 0;
  while (op < SORT_ALG_N && strcmp(argv[1], algo[op].option) != 0) {
    op++;
  }

  if (op >= SORT_ALG_N) {
    printf("unknown option: %s\n", argv[1]);
    puts("see `xsort --help` for available options");
    return EXIT_FAILURE;
  }

  int n = 0;
  int cap = INIT_CAP;
  int32_t *arr = malloc(sizeof(int32_t) * cap);
  if (!arr) {
    puts("error: memory allocation");
    return EXIT_FAILURE;
  }

  FILE *fp;
  bool const tty = (argc == 3);
  if (tty) {
    fp = fopen(argv[2], "r");
    if (!fp) {
      puts("error: opening file");
      return EXIT_FAILURE;
    }
  }

  int32_t x;
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
      arr = realloc(arr, sizeof(int32_t) * cap);
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
