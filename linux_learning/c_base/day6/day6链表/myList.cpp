#include "myList.h"

void print_list(pstu p) {
  while (p) {
    printf("%d ", p->num);
    p = p->next;
  }
}

void list_head_insert(pstu& phead, pstu& ptail, int num) {
  pstu pnew = (pstu)malloc(sizeof(stu));
  pnew->num = num;
  pnew->next = NULL;
  if (NULL == phead) {
    phead = pnew;
    ptail = pnew;
  } else {
    pnew->next = phead;
    phead = pnew;
  }
}

void list_tail_insert(pstu& phead, pstu& ptail, int num) {
  pstu pnew = (pstu)calloc(1, sizeof(stu));
  pnew->num = num;
  if (NULL == phead) {
    phead = pnew;
    ptail = pnew;
  } else {
    ptail->next = pnew;
    ptail = pnew;
  }
}

void list_sort_insert(pstu& phead, pstu& ptail, int num) {
  pstu pnew = (pstu)calloc(1, sizeof(stu));
  pstu p, pre = phead;
  pnew->num = num;
  if (NULL == phead) {
    phead = pnew;
    ptail = pnew;
  } else if (num < phead->num) {
    pnew->next = phead;
    phead = pnew;
  } else {
    p = phead->next;
    while (p && p->num <= num) {
      pre = p;
      p = p->next;
    }
    pre->next = pnew;
    pnew->next = p;
    if (ptail == pre) {
      ptail = pnew;
    }
  }
}

bool list_delete(pstu& phead, pstu& ptail, int num) {
  pstu p, pre = phead;
  if (phead == NULL) {  // 若空链表
    return false;
  }
  if (phead->num == num) {  // 若头结点
    phead = pre->next;
    if (ptail == pre) {
      ptail = NULL;
    }
    free(pre);
    return true;
  }
  p = phead->next;  // 尾部或中部 或不存在对应结点
  while (p) {
    if (p->num == num) {
      pre->next = p->next;
      if (ptail == p) {
        ptail = pre;
      }
      free(p);
      return true;
    }
    pre = p;
    p = p->next;
  }
  return false;
}
void print_list_score(pstu p) {
  while (p) {
    printf("num= %d, score= %f\n", p->num,p->score);
    p = p->next;
  }
}
void list_score_modify(pstu& phead, pstu& ptail, int num, float score) {

}