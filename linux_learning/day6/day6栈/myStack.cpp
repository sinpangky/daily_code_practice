#include "myStack.h"

void init_stack(pStack stack){
  stack->head =NULL;
  stack->size = 0;
}
void pop(pStack stack) {
  if(stack.size==0) {
    return;
  }
  pNode p = stack->head;
  stack->head = p->next;
  free(p);
  stack->size--;
}
void push(pStack stack, int val) {
  pNode pnew = (pNode)calloc(1, sizeof(Node));
  pnew->value = val;
  pnew->next = stack->head;
  stack->head =pnew;
  stack->size++;
}
int top(pStack stack) {
  return stack->head->value;
}
int IsEmpty(pStack stack) {
  if(stack->size) {
    return 1;
  }
  return 0;
}
int size(pStack stack) {
  return stack->size;
}