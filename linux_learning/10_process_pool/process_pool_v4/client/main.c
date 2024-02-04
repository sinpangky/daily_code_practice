#include "head.h"


int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("./client.out IP PORT\n");
    return -1;
  }
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(server_fd, -1, "socket");
  struct sockaddr_in serAddr;
  serAddr.sin_family = AF_INET;
  serAddr.sin_addr.s_addr = inet_addr(argv[1]);
  serAddr.sin_port = htons(atoi(argv[2]));
  int ret;
  char buf[1000] = {0};
  printf("Please input filename to download:\n");
  scanf("%s", buf);

#ifdef T
  strcpy(buf, "testfile");
#endif

#ifdef F
  strcpy(buf, "testfil");
#endif

  ret = connect(server_fd, (struct sockaddr *)&serAddr, sizeof(serAddr));
  ERROR_CHECK(ret, -1, "connect");

  send(server_fd, buf, strlen(buf)+1, 0);
  recv(server_fd, (void*)&ret, sizeof(int), 0);
  if (0 == ret) {
    printf("File start receive\n");
    ReceiveFile(server_fd, buf);
    close(server_fd);
    return 0;
  } else if (-1 == ret) {
    printf("File not exist!\n");
  } else {
    printf("Receive messsage wrong\n");
  }
  close(server_fd);
  return -1;
}
