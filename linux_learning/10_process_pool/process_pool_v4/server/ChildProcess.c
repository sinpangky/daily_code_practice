#include "head.h"
/** build child processes and wait for parent's signal through command_pipe
*/
int MakeChild(ProcessData* processliset_ptr, int process_num) {
  int pipe_fd[2];
  int command_pipe_fd[2];
  char pipe_buf[20] = {0};
  int ret;
  for (int i = 0; i < process_num; i++) {
    socketpair(AF_LOCAL, SOCK_STREAM, 0, pipe_fd);
    pipe(command_pipe_fd);
    pid_t pid = fork();
    if (pid == 0) {
      // CHILD PROCESS
      close(pipe_fd[1]);
      close(command_pipe_fd[1]);
      int client_fd;
      while (1) {  // trap into loop with for parent process signal
        read(command_pipe_fd[0], &ret, sizeof(int));
#ifdef DEBUG
        printf("command received\n");
        printf("ret = %d\n", ret);
#endif
        if (0 == ret) {
          // exit command
          close(pipe_fd[0]);
          close(command_pipe_fd[0]);
          exit(0);
        } else if (1 == ret) {
          // send-file command
#ifdef DEBUG
          printf("send-file succeed\n");
#endif
          ret = RecvFd(pipe_fd[0], &client_fd);  // receive the client fd
          ERROR_CHECK(ret, -1, "RecvFd");
#ifdef DEBUG
          printf("fd received\n");
#endif
          // printf("receive transport file task %d\n", client_fd);
          SendFile(client_fd);
          strcpy(pipe_buf, "task-finish");
          close(client_fd);
          write(pipe_fd[0], pipe_buf, strlen(pipe_buf)+1);
        }
      }
    } else {
      // PARENT PROCESS
      close(pipe_fd[0]);
      close(command_pipe_fd[0]);
      processliset_ptr[i].pid = pid;
      processliset_ptr[i].pipe_fd = pipe_fd[1];
      processliset_ptr[i].command_pipe = command_pipe_fd[1];
      processliset_ptr[i].status = kFree;
    }
  }
  return 0;
}
