#include "sort.h"

// Using Tokuda's sequence up to the largest 32-bit integer;
void shell_sort(int n, int arr[n]) {
  int seq[26] = {1,         4,         9,        20,       46,        103,
                 233,       525,       1182,     2660,     5985,      13467,
                 30301,     68178,     153401,   345152,   776591,    1747331,
                 3931496,   8845866,   19903198, 44782196, 100759940, 226709866,
                 510097200, 1147718700};

  for (int h = 25; h >= 0; h--) {
    int k = seq[h];
    for (int i = k; i < n; i++) {
      int x = arr[i];
      int j = i - k;
      while (j >= 0 && arr[j] > x) {
        arr[j + k] = arr[j];
        j -= k;
      }
      arr[j + k] = x;
    }
  }
}
