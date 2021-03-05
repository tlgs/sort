#include <stdint.h>
#include <stdlib.h>

#include "sort.h"

void swap(int32_t *a, int32_t *b) {
  int32_t t = *a;
  *a = *b;
  *b = t;
}

// Linked-list functions
void list_append(node_t *head, int32_t val) {
  node_t *curr = head;
  while (curr->next) {
    curr = curr->next;
  }

  curr->next = malloc(sizeof(node_t));
  curr->next->value = val;
  curr->next->next = 0;
}

int32_t list_pop_head(node_t **head) {
  node_t *second = (*head)->next;
  int32_t v = (*head)->value;
  free(*head);
  *head = second;

  return v;
}

void list_push_head(node_t **head, int32_t val) {
  node_t *tmp = malloc(sizeof(node_t));
  tmp->value = val;
  tmp->next = *head;
  *head = tmp;
}

int32_t list_pop_at(node_t **head, size_t idx) {
  if (idx == 0) {
    return list_pop_head(head);
  }

  node_t *curr = *head;
  for (size_t i = 0; i < idx - 1; i++) {
    curr = curr->next;
  }

  node_t *tmp = curr->next;
  int32_t v = tmp->value;
  curr->next = tmp->next;
  free(tmp);

  return v;
}
