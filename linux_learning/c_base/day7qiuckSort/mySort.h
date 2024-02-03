#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define SWAP(a, b) \
  {                \
    int temp;      \
    temp = a;      \
    a = b;         \
    b = temp;      \
  }
typedef struct student
{
  int No;
  char name[20];
  int score;
}stu,*pstu;


void PrintArray(int a[], int size);
// void BubbleSort(int a[], int size);
// void InsertSort(int a[], int size);
void QuickSort(int a[],int left,int right);
void HeapSort(int a[], int size);
void MergeSort(int array[], int left, int right);
void CountingSort(int arr[], int size);
int CompareStruct(const void*, const void*);
int CompareIntegers(const void*, const void*);
int CompareStructPointer(const void*, const void*);