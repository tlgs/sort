#ifndef SORT_H
#define SORT_H

#define SORT_ALG_N 17

void bubble_sort(size_t n, int32_t arr[n]);

void cocktail_sort(size_t n, int32_t arr[n]);

void comb_sort(size_t n, int32_t arr[n]);

void cycle_sort(size_t n, int32_t arr[n]);

void flash_sort(size_t n, int32_t arr[n]);

void gnome_sort(size_t n, int32_t arr[n]);

void heap_sort(size_t n, int32_t arr[n]);

void insertion_sort(size_t n, int32_t arr[n]);

void intro_sort(size_t n, int32_t arr[n]);

void merge_sort(size_t n, int32_t arr[n]);

void odd_even_sort(size_t n, int32_t arr[n]);

void quick_sort(size_t n, int32_t arr[n]);

void selection_sort(size_t n, int32_t arr[n]);

void shell_sort(size_t n, int32_t arr[n]);

void stooge_sort(size_t n, int32_t arr[n]);

void strand_sort(size_t n, int32_t arr[n]);

void weak_heap_sort(size_t n, int32_t arr[n]);

// quicksort's partitioning is used in intro_sort
size_t quick_partition(int32_t arr[], size_t lo, size_t hi);

// utils
void swap(int32_t *a, int32_t *b);

typedef struct node {
  int32_t value;
  struct node *next;
} node_t;

void list_append(node_t *head, int32_t val);

void list_push_head(node_t **head, int32_t val);

int32_t list_pop_head(node_t **head);

int32_t list_pop_at(node_t **head, size_t idx);

#endif
