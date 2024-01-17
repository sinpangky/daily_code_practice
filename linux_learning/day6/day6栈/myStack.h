#include <cstdio>
#include <cstdlib>

typedef struct myNode
{
  int value;
  struct myNode* next;
}Node,*pNode;


typedef struct myStack
{
  pNode head;
  int size;
}Stack, *pStack;

void init_stack(pStack stack); 
void pop(pStack stack);
void push(pStack stack, int val);
int top(pStack stack);
int isEmpty(pStack stack);
int size(pStack stack);
