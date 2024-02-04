#include "head.h"

int InitailizeTcp(const char* ip, const char* port, int* sockfd) {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sfd, -1, "socket");
  struct sockaddr_in serAddr;
  bzero(&serAddr, sizeof(serAddr));
  serAddr.sin_family = AF_INET;
  serAddr.sin_port = htons(atoi(port));
  serAddr.sin_addr.s_addr = inet_addr(ip);
  int opt = 1;
  int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  ERROR_CHECK(ret, -1, "setsockopt");

  ret = bind(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
  ERROR_CHECK(ret, -1, "bind");
  listen(sfd, 10);
  *sockfd = sfd;
  return 0;
}