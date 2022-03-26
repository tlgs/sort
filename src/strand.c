#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

typedef struct node {
  int32_t value;
  struct node *next;
} node_t;

int32_t list_pop_front(node_t **head) {
  node_t *second = (*head)->next;
  int32_t v = (*head)->value;
  free(*head);
  *head = second;

  return v;
}

void strand_merge(node_t **result, node_t **sub_list) {
  node_t *p = *result;
  if (!p) {
    p = malloc(sizeof(node_t));
    p->value = list_pop_front(sub_list);
    p->next = 0;
    *result = p;
  }

  while (*sub_list) {
    int32_t v = list_pop_front(sub_list);
    node_t *prev = p;
    while (p && v > p->value) {
      prev = p;
      p = p->next;
    }

    if (p) {
      node_t *tmp = malloc(sizeof(node_t));
      tmp->value = p->value;
      tmp->next = p->next;
      p->value = v;
      p->next = tmp;
    } else {
      prev->next = malloc(sizeof(node_t));
      p = prev->next;
      p->value = v;
      p->next = 0;
    }
  }
}

void strand_sort(size_t n, int32_t arr[n]) {
  node_t *L = malloc(sizeof(node_t));
  L->value = arr[0];
  L->next = 0;

  node_t *p = L;
  for (size_t i = 1; i < n; i++) {
    p->next = malloc(sizeof(node_t));
    p = p->next;
    p->value = arr[i];
    p->next = 0;
  }

  node_t *S = 0;
  while (L) {
    node_t *B = malloc(sizeof(node_t));
    B->value = list_pop_front(&L);
    B->next = 0;

    p = L;
    node_t *prev = p;
    node_t *q = B;
    while (p) {
      if (p->value >= q->value) {
        q->next = malloc(sizeof(node_t));
        q = q->next;
        q->next = 0;

        if (p == L) {
          q->value = list_pop_front(&L);
          p = L;
        } else {
          q->value = p->value;
          prev->next = p->next;
          free(p);
          p = prev->next;
        }
      } else {
        prev = p;
        p = p->next;
      }
    }

    strand_merge(&S, &B);
  }

  for (size_t i = 0; S; i++) {
    arr[i] = list_pop_front(&S);
  }
}
