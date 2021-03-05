#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

void list_merge(node_t **res, node_t **add) {
  if (!(*res)) {
    *res = malloc(sizeof(node_t));
    (*res)->value = list_pop_head(add);
    (*res)->next = 0;
  } else if ((*res)->value > (*add)->value) {
    list_push_head(res, list_pop_head(add));
  }

  node_t *p = *res;
  while (*add) {
    int32_t v = list_pop_head(add);
    while (p && v > p->value) {
      p = p->next;
    }

    if (p) {
      node_t *tmp = malloc(sizeof(node_t));
      tmp->value = p->value;
      tmp->next = p->next;
      p->value = v;
      p->next = tmp;
    } else {
      list_append(*res, v);
    }
  }
}

void strand_sort(size_t n, int32_t arr[n]) {
  node_t *L = malloc(sizeof(node_t));
  L->value = arr[0];
  L->next = 0;
  for (size_t i = 1; i < n; i++) {
    list_append(L, arr[i]);
  }

  node_t *S = 0;
  while (L) {
    node_t *B = malloc(sizeof(node_t));
    B->value = list_pop_head(&L);
    B->next = 0;

    node_t *p = L;
    node_t *q = B;
    for (size_t i = 0; p; i++) {
      if (p->value > q->value) {
        p = p->next;
        list_append(q, list_pop_at(&L, i));
        q = q->next;
        i--;
      } else {
        p = p->next;
      }
    }
    list_merge(&S, &B);
    free(B);
  }
  free(L);

  size_t i = 0;
  while (S) {
    arr[i++] = list_pop_head(&S);
  }
  free(S);
}
