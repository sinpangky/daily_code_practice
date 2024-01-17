#include "mySort.h"

int main() {
  printf("QuickSort:\n");
  int a[SIZE] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
  QuickSort(a, 0, SIZE - 1);
  PrintArray(a, SIZE);
  printf("\n");
  printf("HeapSort:\n");
  int b[SIZE] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
  HeapSort(b, 10);
  PrintArray(b, SIZE);
  printf("\n");
  printf("MergeSort:\n");
  int c[SIZE] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
  MergeSort(c, 0, SIZE - 1);
  PrintArray(c, SIZE);
  printf("\n");
  printf("CountingSort:\n");
  int d[SIZE] = {4, 2, 2, 8, 3, 3, 1, 5, 9, 0};
  CountingSort(d, SIZE);
  PrintArray(d, SIZE);
  printf("\n");
  printf("CompareIntegers:\n");
  qsort(d, SIZE, sizeof(int), CompareIntegers);
  PrintArray(d, SIZE);
  printf("\n");
  printf("CompareStruct:\n");
  stu f[SIZE] = {{1, "zhangsan", 90}, {2, "lisi", 80},   {3, "wangwu", 70},
                 {4, "zhaoliu", 60},  {5, "qianqi", 50}, {6, "sunba", 40},
                 {7, "zhoujiu", 30},  {8, "wuba", 20},   {9, "zhengyi", 10},
                 {10, "wangling", 0}};
  printf("Before:\n");
  for (int i = 0; i < SIZE; i++) {
    printf("%d %s %d\n", f[i].No, f[i].name, f[i].score);
  }
  qsort(f, SIZE, sizeof(stu), CompareStruct);
  printf("After:\n");
  for (int i = 0; i < SIZE; i++) {
    printf("%d %s %d\n", f[i].No, f[i].name, f[i].score);
  }
  printf("\n");
  printf("CompareStructPointer:\n");
  pstu g[SIZE];
  for (size_t i = 0; i < SIZE; i++) {
    g[i] = &f[i];
  }

  qsort(g, SIZE, sizeof(stu*), CompareStructPointer);
  for (int i = 0; i < SIZE; i++) {
    printf("%d %s %d\n", (*g[i]).No, (*g[i]).name, (*g[i]).score);
  }
  return 0;
}
