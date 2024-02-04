#include <stdio.h>

#define N 10
#define SWAP(a, b) \
  {                \
    int temp;      \
    temp = a;      \
    a = b;         \
    b = temp;      \
  }

void BubbleSort(int a[], int size);
void InsertSort(int a[], int size);