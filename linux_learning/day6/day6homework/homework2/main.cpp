#include <cstdio>
#include <cstdlib>

typedef struct Node {
  char data;
  struct Node* next;
} Node, *pNode;

void printList(pNode p) {
  while (p) {
    printf("%c", p->data);
    p = p->next;
  }
  putchar('\n');
}

void insertAfter(pNode& pcur, pNode& pnew) {
  if (pcur == NULL) {
    return;
  }
  pnew->next = pcur->next;
  pcur->next = pnew;
}

pNode buildListAtTail(char a[]) {
  int i = 0;
  if (a[i] == 0) return NULL;
  pNode p = (pNode)calloc(1, sizeof(Node));
  p->data = a[i];  // 初始化树
  pNode pcur = p;
  i++;
  while (a[i]) {
    pNode pnew = (pNode)calloc(1, sizeof(Node));
    pnew->data = a[i];
    insertAfter(pcur, pnew);
    pcur = pnew;
    i++;
  }
  printList(p);
  return p;
}

void insertBefore(pNode& pcur, pNode& pnew) {
  if (pcur == NULL) {
    return;
  }
  pnew->next = pcur;
}

void buildListAtHead(char a[]) {
  int i = 0;
  if (a[i] == 0) return;
  pNode p = (pNode)calloc(1, sizeof(Node));
  p->data = a[i];  // 初始化树
  i++;
  while (a[i]) {
    pNode pnew = (pNode)calloc(1, sizeof(Node));
    pnew->data = a[i];
    insertBefore(p, pnew);
    p = pnew;
    i++;
  }
  printList(p);
}

void insertBySort(pNode& phead, char num) {
  pNode pnew = (pNode)calloc(1, sizeof(Node));
  pNode p, pre = phead;
  pnew->data = num;
  if (NULL == phead) {
    phead = pnew;
  } else if (num < phead->data) {
    pnew->next = phead;
    phead = pnew;
  } else {
    p = phead->next;
    while (p && p->data <= num) {
      pre = p;
      p = p->next;
    }
    pre->next = pnew;
    pnew->next = p;
  }
}

void buildListSort(char a[]) {
  int i = 0;
  pNode p = NULL;
  while (a[i]) {
    insertBySort(p, a[i]);
    i++;
  }
  printList(p);
}

int deleteNode(pNode& phead, char a) {
  pNode p=NULL, pre = phead;
  if ( pre == NULL) return -1;
  if (phead->data == a) {
    phead = pre->next;
    free(pre);
    return 1;
  }
  p = phead->next;
  while (p) {
    if (p->data == a) {
      pre->next = p->next;
      free(p);
      return 1;
    }
    pre = p;
    p = p->next;
  }
  return 0;
}

int main() {
  char a[100];
  gets(a);
  // homework2
  pNode m = buildListAtTail(a);
  // homework3
  buildListAtHead(a);
  // homework4
  buildListSort(a);
  // homework5
  deleteNode(m, 'a');
  printList(m);
  return 0;
}