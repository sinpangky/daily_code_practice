#include <func.h>

void* ChildThread(void* p) {
  int* pp = (int*) p;
  *pp = 100;
  return NULL;
}

int main(int argc, char const* argv[]) {
  int s = 200;
  printf("Before: %d\n",s);
  pthread_t new_thread;
  int ret = pthread_create(&new_thread, NULL, ChildThread, (void*) &s);
  THREAD_ERR_CHECK(ret,"pthread_create");
  pthread_join(new_thread,NULL);
  printf("After: %d\n",s);

  return 0;
}
