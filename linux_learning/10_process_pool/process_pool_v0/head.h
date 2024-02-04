#include <func.h>

typedef enum { FREE, BUSY } WorkStatus;
typedef struct {
  pid_t pid;
  int status;
} ProcessData;

int MakeChild(ProcessData* worklistPtr, int process_num);

int HandleEvent();

int InitailizeTcp(const char* ip, const char* port, int* sockfd);