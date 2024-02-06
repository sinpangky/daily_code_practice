#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "head.h"
#include "task_queue.h"

typedef struct 
{
  pthread_t *thread_id_address;
  int thread_num;
  pthread_cond_t condition;
  TaskQueue task_queue;
}Factory;

int InitializeFactory(Factory *factoryPtr,int thread_num);

int StartFactory(Factory *factoryPtr);

void *ThreadFunction(void* p);

int InitializeTCP(const char *ip, const char *port,int *socketfd);

int SendFile(int client_fd);

#endif