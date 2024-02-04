#include <func.h>

void* ChildThread(void* p) {
  usleep(500);
  long x =5;
  return (void*) x;
}

int main(int argc, char const* argv[]) {
  pthread_t new_thread;
  int ret = pthread_create(&new_thread, NULL, ChildThread, NULL);
  THREAD_ERR_CHECK(ret,"pthread_create");
  long x= 0;
  pthread_join(new_thread,(void**)&x);
  printf("After: %ld\n",x);

  return 0;
}
