#include <stdio.h>

int BinarySearch(int *a, int left, int right, int target) {
  int mid;
  while (left <= right) {
    mid = (left + right) / 2;
    if (a[mid] == target) {
      return mid;
    } else if (a[mid] < target) {
      left = mid+1;
    } else {
      right = mid-1;
    }
  }
  return -1;
}
void BubbleSort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


int main() {
  int a[20] = {123, 1234, 43, 523, 56, 57, 68,  9879, 22, 4235,
               346, 2,    87, 23,  34, 45, 645, 5,    8,  1};
  BubbleSort(a, 20);
  for (int i = 0; i < 20; i++) {
    printf("%-4d ", a[i]);
  }
  printf("\n");
  int pos, ta;
  scanf("%d", &ta);
  pos = BinarySearch(a, 0, 19, ta);
  if (pos == -1) {
    printf("没找到%d", ta);
  } else {
    printf("找到%d在%d位", ta, pos);
  }
  printf("\n");
  return 0;
}