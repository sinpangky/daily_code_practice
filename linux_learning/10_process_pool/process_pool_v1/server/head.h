#include <func.h>

typedef enum { FREE, BUSY } WorkStatus;
typedef struct {
  pid_t pid;
  int status;
  int pipefd;
} ProcessData;

typedef struct ClientFdNode {
  int fd;
  struct ClientFdNode* next;
} ClientFdNode;

typedef struct {
  ClientFdNode* head;
  ClientFdNode* tail;
  int size;
} ClientFdList;

typedef struct {
  int size;
  char content[1000];
}FileToTrans;

// main_function.c
void ClientFdQueueInit(ClientFdList* list);
void ClientFdQueuePush(ClientFdList* list, int fd);
int ClientFdQueuePop(ClientFdList* list);
int ClientFdQueueIsEmpty(ClientFdList* list);
int EpollAdd(int epoll_fd, int fd);

// worker.c
int MakeChild(ProcessData* worklistPtr, int process_num);
// int HandleEvent();

// tcp_init.c
int InitailizeTcp(const char* ip, const char* port, int process_num,
                  int* sockfd);

// transport_fd.c
int SendFd(int pipefd, int fd);
int RecvFd(int pipefd, int* fd);

// transport_file.c
int SendFile(int client_fd);