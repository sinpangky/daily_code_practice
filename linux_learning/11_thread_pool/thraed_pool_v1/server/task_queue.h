#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include "head.h"

typedef struct TaskNode {
  int new_fd;
  struct TaskNode *pnext;
} TaskNode;

typedef struct {
  TaskNode *frontPtr;       // 队列头
  TaskNode *rearPtr;        // 队列尾
  pthread_mutex_t mutex;  // 锁
  int size;          // 当前任务的个数
} TaskQueue;

// 入队
int TaskQueuePush(TaskQueue *pQueue, int new_fd);
// 出队
int TaskQueuePop(TaskQueue *pQueue, TaskNode **pnew);
#endif