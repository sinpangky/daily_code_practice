#include "mySortFunc.h"

void BubbleSort(int a[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int flag = 1;
    for (int j = 0; j < i; j++) {
      if (a[j] > a[j + 1]) {
        SWAP(a[j], a[j + 1])
        flag = 0;
      }
    }
    if (flag == 1) break;
  }
}

void InsertSort(int a[], int size) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;

    // 将arr[i]插入到已排序的序列arr[0...i-1]中
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}