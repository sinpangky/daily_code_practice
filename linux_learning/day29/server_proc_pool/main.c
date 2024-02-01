#include "head.h"

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("./process_pool IP PORT PROCESS_NUM\n");
    return -1;
  }

  int process_num = atoi(argv[3]);  // number of child processes
  ProcessData *worklist =
      (ProcessData *)calloc(process_num, sizeof(ProcessData));
  MakeChild(worklist, process_num);  // create child processes

  int sockfd;
  InitailizeTcp(argv[1], argv[2], process_num, &sockfd);  // initialize TCP

  int epoll_fd = epoll_create(1);
  EpollAdd(epoll_fd, sockfd);
  int i;
  for (i = 0; i < process_num; i++) {
    EpollAdd(epoll_fd, worklist[i].pipefd);
  }
  int ready_fd_num, new_fd;
  struct epoll_event *evs =
      (struct epoll_event *)calloc(process_num + 1, sizeof(struct epoll_event));
  struct sockaddr_in client;
  int address_length, finish_flag;
  // initialize client file descriptor queue
  ClientFdList clientfd_list;
  ClientFdQueueInit(&clientfd_list);

  while (1) {
    // check if there are any new connections
    if (!ClientFdQueueIsEmpty(&clientfd_list)) {
      for (i = 0; i < process_num; i++) {
        if (FREE == worklist[i].status) {
          new_fd = ClientFdQueuePop(&clientfd_list);
          SendFd(worklist[i].pipefd, new_fd);
          worklist[i].status = BUSY;
          printf("Send client %d to process %d\n", new_fd, worklist[i].pipefd);
          close(new_fd);
          break;
        }
      }
    }

    ready_fd_num =
        epoll_wait(epoll_fd, evs, process_num + 1, -1);  // wait for events
    for (i = 0; i < ready_fd_num; i++) {
      if (sockfd == evs[i].data.fd) {  // new connection
        address_length = sizeof(client);
        new_fd = accept(sockfd, (struct sockaddr *)&client,
                        (socklen_t *)&address_length);
        printf("client ip = %s, port = %d\n", inet_ntoa(client.sin_addr),
               ntohs(client.sin_port));
        ClientFdQueuePush(&clientfd_list, new_fd);  // add to queue
      } else {  // check if any child processes have finished
        for (int j = 0; j < process_num; j++) {
          if (worklist[j].pipefd == evs[i].data.fd) {
            read(worklist[j].pipefd, &finish_flag, sizeof(finish_flag));
            worklist[j].status = FREE;
            printf("process %d finished task\n", worklist[j].pid);
            break;
          }
        }
      }
    }
  }
  return 0;
}
