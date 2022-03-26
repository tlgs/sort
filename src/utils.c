#include <stddef.h>
#include <stdint.h>

#include "sort.h"

void swap(int32_t *a, int32_t *b) {
  int32_t t = *a;
  *a = *b;
  *b = t;
}
