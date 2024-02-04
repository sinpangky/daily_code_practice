#include "head.h"

int command_pipefd[2];
void ExitSigFunciton(int signum);

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("./server.out IP PORT PROCESS_NUM\n");
    return -1;
  }
  int listen_fd;
  pipe(command_pipefd);
  signal(SIGUSR1, ExitSigFunciton);

  // create child process
  int process_num = atoi(argv[3]);
  ProcessData *process_list =
      (ProcessData *)calloc(process_num, sizeof(ProcessData));
  int ret = MakeChild(process_list, process_num);
  ERROR_CHECK(ret, -1, "Makechild");

  //  Initialize Tcp
  InitializeTcp(argv[1], argv[2], process_num, &listen_fd);

  // Add to epoll queue
  int epoll_fd = epoll_create(1);
  EpollAdd(epoll_fd, listen_fd);
  EpollAdd(epoll_fd, command_pipefd[0]);
  for (int i = 0; i < process_num; i++) {
    EpollAdd(epoll_fd, process_list[i].pipe_fd);
  }

  int ready_fd_num, client_fd;
  struct epoll_event *events =
      (struct epoll_event *)calloc(process_num + 2, sizeof(struct epoll_event));
  struct sockaddr_in client_addr;
  socklen_t address_length = sizeof(client_addr);
  ClientFdList clientfd_list;
  ClientFdQueueInit(&clientfd_list);

  char pipe_buf[20] = {0};

  // start to check epoll queue
  while (1) {
    ready_fd_num = epoll_wait(epoll_fd, events, process_num + 2, -1);
    for (int i = 0; i < ready_fd_num; i++) {
      if (command_pipefd[0] == events[i].data.fd) {
        // exit command signal
        close(listen_fd);
        while (!ClientFdQueueIsEmpty(&clientfd_list)) {
          client_fd = ClientFdQueuePop(&clientfd_list);
          close(client_fd);
        }
        ret = 0;
        for (int j = 0; j < process_num; j++) {
          write(process_list[j].command_pipe, &ret, sizeof(int));
#ifdef DEBUG
          printf("%d   ", j);
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
        for (int j = 0; j < process_num; j++) {
          wait(NULL);
          printf("close one child process succeed\n");
        }
        goto EXIT;
      } else if (listen_fd == events[i].data.fd) {
        // new connection
        client_fd =
            accept(listen_fd, (struct sockaddr *)&client_addr, &address_length);
        printf("client ip = %s, port = %d\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));
        ClientFdQueuePush(&clientfd_list, client_fd);
      } else {
        // task finished
        for (int j = 0; j < process_num; j++) {
          if (process_list[j].pipe_fd == events[i].data.fd) {
            recv(process_list[j].pipe_fd, pipe_buf, sizeof(pipe_buf), 0);
            process_list[j].status = kFree;
            printf("process %d finished task\n", j);
            break;
          }
        }
      }
    }
    // check client queue
    if (!ClientFdQueueIsEmpty(&clientfd_list)) {
      for (int i = 0; i < process_num; i++) {
        if (kFree == process_list[i].status) {
          client_fd = ClientFdQueuePop(&clientfd_list);
          ret = 1;
          write(process_list[i].command_pipe, &ret, sizeof(int));
          SendFd(process_list[i].pipe_fd, client_fd);
          process_list[i].status = kBusy;
          printf("Send client %d to process %d\n", client_fd, i);
          close(client_fd);
          break;
        }
      }
    }
  }

EXIT:
  close(epoll_fd);

  return 0;
}

void ExitSigFunciton(int signum) {
  printf("start to graceful exit\n");
  write(command_pipefd[1], "exit", 5);
}