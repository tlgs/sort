#ifndef SORT_H
#define SORT_H

#define SORT_ALG_N 8

void swap(int32_t *a, int32_t *b);

void bubble_sort(size_t n, int32_t arr[n]);

void cocktail_sort(size_t n, int32_t arr[n]);

void comb_sort(size_t n, int32_t arr[n]);

void insertion_sort(size_t n, int32_t arr[n]);

void merge_sort(size_t n, int32_t arr[n]);

void quick_sort(size_t n, int32_t arr[n]);

void selection_sort(size_t n, int32_t arr[n]);

void shell_sort(size_t n, int32_t arr[n]);

#endif
