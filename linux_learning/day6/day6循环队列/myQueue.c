#include "myQueue.h"

void InitQueue(sqQueue *Q) { Q->front = Q->rear = 0; }
int isEmpty(sqQueue *Q) {
  if (Q->front == Q->rear) return 1;
  return 0;
}
int EnQueue(sqQueue *Q, ElemType x) {
  if ((Q->rear + 1) % MaxSize == Q->front) return 0;
  Q->data[Q->rear] = x;
  Q->rear = (Q->rear + 1) % MaxSize;
  return 1;
}
int DeQueue(sqQueue *Q, ElemType *x) {
  if (Q->front == Q->rear) return 0;
  *x = Q->data[(Q->rear - 1) % MaxSize];
  Q->rear = (Q->rear - 1) % MaxSize;
  return 1;
}