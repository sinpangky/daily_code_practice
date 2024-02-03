#include <cstdio>
#include <cstdlib>

typedef int ElementType;
typedef struct list_node {
  int data;
  struct list_node *next;
} ListNode, *pListNode;

void InsertBySort(pListNode&, ElementType);
void PrintList(pListNode);
void MergeSortedList(pListNode& to, pListNode from);
void ReverseList(pListNode&);
pListNode FindFourthNodeFromEnd(pListNode);
pListNode FindMiddlehNode(pListNode);
int IsLoop(pListNode);
pListNode IsIntersect(pListNode,pListNode);
void RemoveDuplicate(pListNode);
void SplitListByOddEven(pListNode from,pListNode& to);