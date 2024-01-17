#include <stdio.h>
#include <stdlib.h>

#define N 30

int main() {
  int array[N] = {1, -3, 6,  4, -3, 6, -8, 1,  2,  -7, 65, 65, 68, 1, -3,
                  6, 4,  -3, 6, -8, 1, 2,  -7, 65, 65, 68, 1,  -3, 6, 4};
  long long *bitmap = (long long *)calloc((1 << 26), sizeof(long long));
  int i, pos, bit_pos;
  for (i = 0; i < N; i++) {
    unsigned int value = array[i] + (1u << 31);
    pos = value / 64;
    bit_pos = value % 64;
    if ((long long)1 << bit_pos & bitmap[pos]) {
    } else {
      bitmap[pos] |= (long long)1 << bit_pos;
      printf("%3d", array[i]);
    }
  }
  printf("\n");
  free(bitmap);
  return 0;
}