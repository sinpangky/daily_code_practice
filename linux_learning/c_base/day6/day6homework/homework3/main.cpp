#include "my_list.h"

int main() {
  // initialize the list a and b
  ElementType a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  pListNode list_a = NULL, list_b = NULL;
  for (size_t i = 0; i < 10; i = i + 2) {
    InsertBySort(list_a, a[i]);
  }
  for (size_t i = 1; i < 10; i = i + 2) {
    InsertBySort(list_b, a[i]);
  }
  PrintList(list_a);
  PrintList(list_b);

  // homework 6
  printf("homework 6:\n");
  MergeSortedList(list_a, list_b);
  PrintList(list_a);

  // homework 7
  printf("homework 7:\n");
  ReverseList(list_a);
  PrintList(list_a);

  // homework 8
  printf("homework 8:\n");
  pListNode s = FindFourthNodeFromEnd(list_a);
  printf("%d\n", s->data);

  // homework 9
  printf("homework 9:\n");
  s = FindMiddlehNode(list_a);
  printf("%d\n", s->data);

  // homework 10
  printf("homework 10:\n");
  printf("改变前是否有环:%d\n", IsLoop(list_a));
  list_a->next->next->next->next->next = list_a->next;
  printf("改变后是否有环:%d\n", IsLoop(list_a));
  list_a->next->next->next->next->next = NULL;

  // homework 11
  printf("homework 11:\n");
  list_b = NULL;
  for (size_t i = 1; i < 10; i = i + 2) {
    InsertBySort(list_b, a[i]);
  }
  list_a = NULL;
  for (size_t i = 0; i < 10; i = i + 2) {
    InsertBySort(list_a, a[i]);
  }
  s = IsIntersect(list_a, list_b);
  if (s) {
    printf("改变前相交点为%d\n", s->data);
  } else {
    printf("改变前不相交\n");
  }
  pListNode p = list_b;
  for (int i = 0; i < 4; i++) {
    p = p->next;
  }
  p->next = list_a->next;
  s = IsIntersect(list_a, list_b);
  if (s) {
    printf("改变后相交点为%d\n", s->data);
  } else {
    printf("改变后不相交\n");
  }

  // homework 12
  printf("homework 12:\n");
  p = list_b->next;
  for (int i = 0; i < 4; i++) {
    p->data = 1;
    p = p->next;
  }
  PrintList(list_b);
  RemoveDuplicate(list_b);
  PrintList(list_b);

  // homework 13
  SplitListByOddEven(list_b,list_a);
  PrintList(list_b);
  PrintList(list_a);
  return 0;
}