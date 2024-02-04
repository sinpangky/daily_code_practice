#include <func.h>
// #define DEBUG

typedef enum {
  kFree,
  kBusy
} WorkStatus;

typedef struct {
  int pid;
  int status;
  int pipe_fd;
  int command_pipe;
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
} FileToTrans;

// MainFunction.c
void ClientFdQueueInit(ClientFdList* list);
void ClientFdQueuePush(ClientFdList* list, int fd);
int ClientFdQueuePop(ClientFdList* list);
int ClientFdQueueIsEmpty(const ClientFdList* list);
int EpollAdd(int epoll_fd, int fd);

// ChildProcess.c
int MakeChild(ProcessData* worklist_ptr, int process_num);

// TcpInit.c
int InitializeTcp(const char* ip, const char* port, int process_num, int* sockfd_ptr);

// TransportFd.c
int SendFd(int pipefd, int fd);
int RecvFd(int pipefd, int* fd);

// TransportFile.c
int SendFile(int client_fd);
