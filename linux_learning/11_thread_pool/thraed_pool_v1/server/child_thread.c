#include "factory.h"

void MutexClean(void *p){
  pthread_mutex_t *mutexPtr = (pthread_mutex_t *)p;
  pthread_mutex_unlock(mutexPtr);
}

void *ThreadFunction(void* param_input){
  Factory *factoryPtr = (Factory *)param_input;
  TaskQueue *queuePtr = &factoryPtr->task_queue;
  TaskNode *new_nodePtr;
  int task_flag;
  while (1)
  {
    pthread_mutex_lock(&queuePtr->mutex);
    pthread_cleanup_push(MutexClean,&queuePtr->mutex);

    if(!queuePtr->size){
      pthread_cond_wait(&factoryPtr->condition,&queuePtr->mutex);
    }
    task_flag = TaskQueuePop(queuePtr,&new_nodePtr);
    pthread_cleanup_pop(1);
    if(!task_flag){
      printf("send file\n");
      
      SendFile(new_nodePtr->new_fd);
      close(new_nodePtr->new_fd);
      free(new_nodePtr);
    }
  }
  
}


int SendFile(int client_fd);