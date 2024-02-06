#include "factory.h"

int InitializeFactory(Factory *factoryPtr, int thread_num) {
  int retval;
  bzero(factoryPtr, sizeof(Factory));
  factoryPtr->thread_id_address =
      (pthread_t *)calloc(thread_num, sizeof(pthread_t));
  factoryPtr->thread_num = thread_num;
  retval = pthread_cond_init(&factoryPtr->condition, NULL);
  THREAD_ERR_CHECK(retval, "pthread_cond_init");
  pthread_mutex_init(&factoryPtr->task_queue.mutex, NULL);
  return 0;
}

int StartFactory(Factory *factoryPtr) {
  int retval;
  for (int i = 0; i < factoryPtr->thread_num; i++) {
    retval = pthread_create(factoryPtr->thread_id_address + i, NULL,
                            ThreadFunction, factoryPtr);
    THREAD_ERR_CHECK(retval, "pthread_create");
  }
  return 0;
}