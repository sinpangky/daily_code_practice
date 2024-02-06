#include "factory.h"

int command_pipe[2];

int AddToEpoll(int epoll_fd, int input_fd);

void ExitSignalFunction(int sig_num);

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("./server.out IP PORT THREAD_NUM\n");
    return -1;
  }

  pipe(command_pipe);
  // build a parent process to control the graceful exit
  if (fork()) {
    // PARENT PROCESS
    signal(SIGUSR1, ExitSignalFunction);
    wait(NULL);
    exit(0);
  }

  // CHILD PROCESS, as the main process
  int thread_num = atoi(argv[3]);
  Factory fac;
  InitializeFactory(&fac, thread_num);
  StartFactory(&fac);
  int socket_fd, client_fd;
  InitializeTCP(argv[1], argv[2], &socket_fd);

  // prepare for accepting new connections
  struct sockaddr_in client_address;
  socklen_t address_length = sizeof(client_address);

  TaskQueue *queuePtr = &fac.task_queue;
  int epoll_fd = epoll_create(1);
  AddToEpoll(epoll_fd, socket_fd);
  AddToEpoll(epoll_fd, command_pipe[0]);
  int ready_fd_num, i, j;
  struct epoll_event events[2];
  while (1) {
    ready_fd_num = epoll_wait(epoll_fd, events, 2, -1);
    for (i = 0; i < ready_fd_num; i++) {
      if (events[i].data.fd == socket_fd) {
        client_fd = accept(socket_fd, (struct sockaddr *)&client_address,
                           &address_length);
        ERROR_CHECK(client_fd, -1, "accept");
        printf("add new task into queue\n");
        TaskQueuePush(queuePtr, client_fd);
        // wake up one child thread
        pthread_cond_signal(&fac.condition);
      } else if (events[i].data.fd == command_pipe[0]) {
        printf("graceful exit start\n");
        close(socket_fd);
        for (j = 0; j < thread_num; j++) {
          pthread_cancel(fac.thread_id_address[j]);
        }
        for (j = 0; j < thread_num; j++) {
          pthread_join(fac.thread_id_address[j], NULL);
        }
        printf("exit succeed\n");
        exit(0);
      }
    }
  }

  return 0;
}

/** if hold the SIGUSR1 signal, send exit command to epoll-wait queue.
 */
void ExitSignalFunction(int sig_num) {
  printf("Start to gracefully exit\n");
  write(command_pipe[1], "exit", 5);
}
int AddToEpoll(int epoll_fd, int input_fd) {
  struct epoll_event event;
  event.data.fd = input_fd;
  event.events = EPOLLIN;
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, input_fd, &event);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}