#include "mySortFunc.h"

int main(){
  int a[10];
  for (int i = 0; i < 10; i++)
  {
    a[i] = 20-i;
  }
  BubbleSort(a,10);
  for (int i = 0; i < 10; i++)
  {
    printf("%2d ",a[i]);
  }
  printf("\n");
  
  for (int i = 0; i < 10; i++)
  {
    a[i] = 20-i;
  }
  BubbleSort(a,10);
  for (int i = 0; i < 10; i++)
  {
    printf("%d ",a[i]);
  }
  printf("\n");
}