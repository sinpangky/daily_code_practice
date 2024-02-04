#include "head.h"

int MakeChild(ProcessData *worklistPtr, int process_num) {
  int i;
  for (i = 0; i < process_num; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      HandleEvent();
    }
    worklistPtr[i].pid = pid;
    worklistPtr[i].status = FREE;
  }
  return 0;
}

int HandleEvent() {
  while (1)
    ;
  return 0;
}