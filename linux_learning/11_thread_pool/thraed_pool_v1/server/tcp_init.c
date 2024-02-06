#include "factory.h"

int InitializeTCP(const char *ip, const char *port, int *socketfd) {
  // create a TCP socket
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sfd, -1, "socket");

  // Set socket options to allow reuse of the address
  int opt = 1;
  int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
  ERROR_CHECK(ret, -1, "socketopt");

  // Bind the socket to the specified IP address and port
  struct sockaddr_in serAddr;
  bzero(&serAddr, sizeof(serAddr));
  serAddr.sin_family = AF_INET;
  serAddr.sin_port = htons(atoi(port));
  serAddr.sin_addr.s_addr = inet_addr(ip);
  ret = bind(sfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
  ERROR_CHECK(ret, -1, "bind");

  // Start listening for incoming connections, connections <= 10
  listen(sfd, 10);

  // Store the socket file descriptor in the provided pointer
  *socketfd = sfd;

  return 0;
}