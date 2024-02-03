#include "head.h"

void HandleEvent(int pipefd) {
  int new_fd, finish_flag =1;
  while (1){
    // receive task
    RecvFd(pipefd,&new_fd);
    printf("receive parent task %d\n",new_fd);
    // send file to client
    SendFile(new_fd);
    close(new_fd);
    // give parent process the finish signal
    write(pipefd,&finish_flag,sizeof(finish_flag));
  }
}

int MakeChild(ProcessData *worklist, int process_num) {
  int i;
  int pipefd[2];
  for (i = 0; i < process_num; i++) {
    socketpair(AF_LOCAL, SOCK_STREAM, 0, pipefd);
    pid_t pid = fork();
    if (0 == pid) {
      close(pipefd[1]);
      HandleEvent(pipefd[0]);
    }
    // parent process
    close(pipefd[0]);
    worklist[i].pid = pid;
    worklist[i].status = FREE;
    worklist[i].pipefd = pipefd[1];
  }
  return 0;
}
