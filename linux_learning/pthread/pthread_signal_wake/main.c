#include <func.h>

typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t condition;
} ShareResource, *pShareResource;

void* child_function_1(void* thread_argv) {
  pShareResource p = (pShareResource)thread_argv;
  pthread_mutex_lock(&p->mutex);  // 加锁
  printf("child_thread is waiting condition signal\n");
  pthread_cond_wait(&p->condition, &p->mutex);
  pthread_mutex_unlock(&p->mutex);  // 解锁
  printf("child_thread received signal\n");
  pthread_exit(NULL);
}

int main(int argc, char const* argv[]) {
  // 共享资源初始化
  ShareResource share;
  pthread_mutex_init(&share.mutex, NULL);
  pthread_cond_init(&share.condition, NULL);

  // 线程创建
  pthread_t child_thread_1, child_thread_2;
  pthread_create(&child_thread_1, NULL, child_function_1, (void*)&share);
  // 睡眠5s后发信号
  printf("sleep for 5s\n");
  sleep(5);
  printf("sending signal\n");
  pthread_cond_signal(&share.condition);
  pthread_join(child_thread_1, NULL);
  // 共享资源销毁
  pthread_mutex_destroy(&share.mutex);
  pthread_cond_destroy(&share.condition);

  return 0;
}
