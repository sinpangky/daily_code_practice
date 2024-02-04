#include <func.h>

void* child_thread(void* thread_argv) {
  while (1) {
    pthread_testcancel();
  }
  printf("this is child thread\n");
  pthread_exit(NULL);
}

int main(int argc, char const* argv[]) {
  pthread_t child;
  int ret = pthread_create(&child, NULL, child_thread, NULL);
  THREAD_ERR_CHECK(ret, "pthread_create");
  sleep(2);
  printf("pthread_cancel begins\n");
  ret = pthread_cancel(child);
  THREAD_ERR_CHECK(ret, "pthread_cancel");
  pthread_join(child, NULL);
  printf("pthread_join finished\n");
  return 0;
}
