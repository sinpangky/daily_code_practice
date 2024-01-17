#include "myQueue.h"

int main() {
  sqQueue Q;
  int ret;           // 存储返回值
  ElemType element;  // 存储出队元素 
  InitQueue(&Q);
  ret = isEmpty(&Q);
  if (ret) {
    printf("队列为空\n");
  } else {
    printf("队列不为空\n");
  }
  EnQueue(&Q, 3);
  EnQueue(&Q, 4);
  EnQueue(&Q, 5);
  ret = EnQueue(&Q, 6);
  // 因为队列最大长度为 MaxSize-1 个元素，因此 7 入队时失败 
  ret=EnQueue(&Q,7);
  if (ret) {
    printf("入队成功\n");
  } else {
    printf("入队失败\n");
  }
  ret = DeQueue(&Q, &element);
  if (ret) {
    printf("出队成功,元素值为 %d\n", element);
  } else {
    printf("出队失败\n");
  }
  ret = DeQueue(&Q, &element);
  if (ret) {
    printf("出队成功,元素值为 %d\n", element);
  } else {
    printf("出队失败\n");
  }
  ret = EnQueue(&Q, 8);
  if (ret) {
    printf("入队成功\n");
  } else {
    printf("入队失败\n");
  }
  return 0;
}