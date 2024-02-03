#include <func.h>
int* heap;

void* ChildThread(void* p) {
  heap[0] = 2;
  return NULL;
}

int main(int argc, char const* argv[]) {
  heap = (int*)malloc(20);
  heap[0] = 1;
  printf("Before: %d\n",heap[0]);
  pthread_t new_thread;
  int ret = pthread_create(&new_thread, NULL, ChildThread, NULL);
  THREAD_ERR_CHECK(ret,"pthread_create");
  pthread_join(new_thread,NULL);
  printf("After: %d\n",heap[0]);

  return 0;
}
