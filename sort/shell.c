#include <stdint.h>

#include "sort.h"

// uses Tokuda's sequence (A108870 in the OEIS)
void shell_sort(size_t n, int32_t arr[n]) {
  size_t const seq[30] = {
      1,         4,          9,          20,         46,          103,
      233,       525,        1182,       2660,       5985,        13467,
      30301,     68178,      153401,     345152,     776591,      1747331,
      3931496,   8845866,    19903198,   44782196,   100759940,   226709866,
      510097200, 1147718700, 2582367076, 5810325920, 13073233321, 29414774973};

  for (int h = 29; h >= 0; h--) {
    size_t k = seq[h];
    for (size_t i = k; i < n; i++) {
      int32_t x = arr[i];
      size_t j = i;
      while (j >= k && x < arr[j - k]) {
        arr[j] = arr[j - k];
        j -= k;
      }
      arr[j] = x;
    }
  }
}
