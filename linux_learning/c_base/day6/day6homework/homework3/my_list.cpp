#include "my_list.h"

void InsertBySort(pListNode& phead, ElementType num) {
  pListNode pnew = (pListNode)calloc(1, sizeof(ListNode));
  pListNode p, pre = phead;
  pnew->data = num;
  if (NULL == phead) {  // 链表空
    phead = pnew;
  } else if (num < phead->data) {  // 小于头结点
    pnew->next = phead;
    phead = pnew;
  } else {  // 大于等于头结点
    p = phead->next;
    while (p && p->data <= num) {
      pre = p;
      p = p->next;
    }
    pre->next = pnew;
    pnew->next = p;
  }
}

void PrintList(pListNode node) {
  while (node) {
    printf("%d->", node->data);
    node = node->next;
  }
  printf("NULL\n");
}

void MergeSortedList(pListNode& to, pListNode from) {
  if (!to || !from) {
    to = (to == NULL) ? from : to;
    return;
  }
  pListNode temp = NULL, p_a = to, p_b = from;
  if (p_b->data < p_a->data) to = from;
  while (p_a && p_b) {
    if (p_b->data < p_a->data) {  // p_b的值小于p_a
      while (p_b->next && p_b->next->data < p_a->data) {
        p_b = p_b->next;
      }
      temp = p_b->next;
      p_b->next = p_a;
      p_b = temp;
    } else {
      while (p_a->next && p_a->next->data < p_b->data) {
        p_a = p_a->next;
      }
      temp = p_a->next;
      p_a->next = p_b;
      p_a = temp;
    }
  }
}

void ReverseList(pListNode& list) {
  if (!list || !list->next) return;
  pListNode pre = NULL, p = list->next;
  list->next = pre;
  while (p) {
    pre = list;
    list = p;
    p = p->next;
    list->next = pre;
  }
}

pListNode FindFourthNodeFromEnd(pListNode list) {
  pListNode fast = list, slow = list;
  for (int i = 0; i < 4; i++) {
    if (fast == NULL) return NULL;
    fast = fast->next;
  }
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }
  return slow;
}

pListNode FindMiddlehNode(pListNode list) {
  pListNode fast = list, slow = list;
  if (fast == NULL) return NULL;
  while (fast) {
    if (fast->next) {
      fast = fast->next->next;
      slow = slow->next;
    } else {
      fast = fast->next;
    }
  }
  return slow;
}

int IsLoop(pListNode list) {
  pListNode fast = list, slow = list;
  if (!fast || !fast->next) return 0;
  while (fast) {
    if (!fast->next) return 0;
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) return 1;
  }
  return 0;
}

pListNode IsIntersect(pListNode list_a, pListNode list_b) {
  int i, j, k;
  pListNode temp_a, temp_b;
  // 得到链表长短
  for (i = 0, temp_a = list_a; temp_a; i++) {
    temp_a = temp_a->next;
  }
  for (j = 0, temp_b = list_b; temp_b; j++) {
    temp_b = temp_b->next;
  }
  // 消去链表长短不齐
  if (i > j) {
    for (k = 0; k < i - j; k++) {
      list_a = list_a->next;
    }
  } else {
    for (k = 0; k < j - i; k++) {
      list_b = list_b->next;
    }
  }
  // 开始比较
  while (list_a && list_b) {
    if (list_a == list_b) return list_a;
    list_a = list_a->next;
    list_b = list_b->next;
  }
  return NULL;
}

void RemoveDuplicate(pListNode a) {
  pListNode head = a, pre, p;
  while (head) {
    pre = head;
    p = head->next;
    while (p) {
      if (p->data == head->data) {
        pre->next = p->next;
        free(p);
        p = pre->next;
      } else {
        pre = p;
        p = p->next;
      }
    }
    head = head->next;
  }
}

void ListTailInsert(pListNode& ptail, pListNode pnew) {
  if (ptail == NULL) {
    ptail = pnew;
    pnew->next = NULL;
    return;
  }
  ptail->next = pnew;
  ptail = pnew;
  pnew->next = NULL;

}

void SplitListByOddEven(pListNode from, pListNode& to) {
  pListNode pre, p = from;
  pre = (pListNode)calloc(1, sizeof(ListNode));
  pre->next = p;
  pListNode tail_1 = NULL, tail_2 = NULL;
  to = from->next;
  bool flag = true;
  while (p) {
    if (flag) {
      pre->next = p->next;
      ListTailInsert(tail_1, p);
      p = pre->next;
      flag = false;
    } else {
      pre->next = p->next;
      ListTailInsert(tail_2, p);
      p = pre->next;
      flag = true;
    }
  }
}