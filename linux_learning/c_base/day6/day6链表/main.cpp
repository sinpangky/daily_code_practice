#include "myList.h"

int main() {
  pstu phead = NULL, ptail = NULL;  // 链表头指针,尾指针
  // list_head_insert(phead,ptail,5);
  int i;
  while (scanf("%d", &i)!=EOF) {
    list_sort_insert(phead, ptail, i);
  }
  printf("\n");
  print_list(phead);
  printf("\n");
  list_delete(phead,ptail,1);
  print_list(phead);
  printf("%d",sizeof(char*));
  return 0;
}