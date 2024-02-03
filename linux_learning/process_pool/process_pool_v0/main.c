#include "head.h"

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    printf("./process_pool IP PORT PROCESS_NUM\n");
    return -1;
  }

  int process_num = atoi(argv[3]);  // 子进程数
  ProcessData *worklistPtr =
      (ProcessData *)calloc(process_num, sizeof(ProcessData));
  MakeChild(worklistPtr, process_num);  // 创建子进程

  int sockfd;
  InitailizeTcp(argv[1], argv[2], &sockfd);  // 初始化TCP

  while (1)
    ;
  return 0;
}
