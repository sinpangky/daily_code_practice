#include <func.h>

void* child_start(void* thread_parameter){
  time_t now;
  time(&now);
  char* p = ctime(&now);
  printf("child time : %s",p);
  sleep(2);
  printf("child time : %s",p);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t child_thread;
  int ret = pthread_create(&child_thread, NULL, child_start, NULL);
  THREAD_ERR_CHECK(ret,"pthread_create");
  sleep(1);
  time_t now;
  time(&now);
  char* p = ctime(&now);
  printf("main time : %s",p);
  pthread_join(child_thread,NULL);
  return 0;
}
