#include <func.h>

void clean_function(void* p) { printf("the input is: %s\n", (char*)p); }

void* child_thread(void* thread_argv) {
  char test_a[20] = "this is first.";
  char test_b[20] = "this is second.";
  pthread_cleanup_push(clean_function, (void*)test_a);
  pthread_cleanup_push(clean_function, (void*)test_b);
  while (1) {
    pthread_testcancel();
  }
  pthread_exit(NULL);
  pthread_cleanup_pop(1);
  pthread_cleanup_pop(1);
}

int main(int argc, char const* argv[]) {
  pthread_t child;
  int ret = pthread_create(&child, NULL, child_thread, NULL);
  THREAD_ERR_CHECK(ret, "pthread_create");
  // sleep(2);
  printf("pthread_cancel begins\n");
  ret = pthread_cancel(child);
  THREAD_ERR_CHECK(ret, "pthread_cancel");
  pthread_join(child, NULL);
  printf("pthread_join finished\n");
  return 0;
}
