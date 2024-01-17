#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct studnet {
  int num;
  float score;
  struct studnet* next;
} stu, *pstu;

void print_list(pstu p);
void list_head_insert(pstu& phead, pstu& ptail, int num);
void list_tail_insert(pstu& phead, pstu& ptail, int num);
void list_sort_insert(pstu& phead, pstu& ptail, int num);
bool list_delete(pstu& phead, pstu& ptail, int num);
void print_list_score(pstu p);
void list_score_modify(pstu& phead, pstu& ptail, int num, float score);
