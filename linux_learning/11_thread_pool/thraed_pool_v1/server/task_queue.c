#include "task_queue.h"

// 入队
int TaskQueuePush(TaskQueue *pQueue, int new_fd) {
  TaskNode *pnew =
      (TaskNode *)calloc(1, sizeof(TaskNode));  // 新结点申请空间
  pnew->new_fd = new_fd;
  pthread_mutex_lock(&pQueue->mutex);
  // 放队列，尾插法
  if (!pQueue->rearPtr) {
    pQueue->frontPtr = pnew;
    pQueue->rearPtr = pnew;
  } else {
    pQueue->rearPtr->pnext = pnew;
    pQueue->rearPtr = pnew;
  }
  pQueue->size++;
  pthread_mutex_unlock(&pQueue->mutex);
  return 0;
}
// 出队
int TaskQueuePop(TaskQueue *pQueue, TaskNode **pnew) {
  if(pQueue->size)//需要判断
    {
        *pnew=pQueue->frontPtr;
        pQueue->frontPtr=pQueue->frontPtr->pnext;
        pQueue->size--;//队列长度减1
        if(NULL==pQueue->frontPtr)//当出队时，队列为空时，队尾要改变
        {
            pQueue->rearPtr=NULL;
        }
    }else{
        return -1;
    }
    return 0;
}