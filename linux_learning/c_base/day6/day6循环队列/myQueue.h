#include <stdio.h>
#include <stdlib.h>


#define MaxSize 6
typedef int ElemType;
typedef struct 
{
  ElemType data[MaxSize];
  int front,rear;
}sqQueue;

void InitQueue(sqQueue *Q);
int isEmpty(sqQueue *Q);
int EnQueue(sqQueue *Q,ElemType x);
int DeQueue(sqQueue *Q,ElemType *x);
