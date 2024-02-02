#include "head.h"

/**
 * @brief Initializes a TCP socket and binds it to the specified IP address and port.
 * 
 * @param ip The IP address to bind the socket to.
 * @param port The port number to bind the socket to.
 * @param listen_max_num The maximum number of pending connections that can be queued.
 * @param sockfd Pointer to store the file descriptor of the initialized socket.
 * @return 0 on success, -1 on failure.
 */
int InitailizeTcp(const char* ip, const char* port, int listen_max_num, int* sockfd) {
  // Create a TCP socket
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sfd, -1, "socket");

  // Set socket options to allow reuse of the address
  int opt = 1;
  int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  ERROR_CHECK(ret, -1, "setsockopt");

  // Bind the socket to the specified IP address and port
  struct sockaddr_in serAddr;
  bzero(&serAddr, sizeof(serAddr));
  serAddr.sin_family = AF_INET;
  serAddr.sin_port = htons(atoi(port));
  serAddr.sin_addr.s_addr = inet_addr(ip);
  ret = bind(sfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
  ERROR_CHECK(ret, -1, "bind");

  // Start listening for incoming connections
  listen(sfd, listen_max_num);

  // Store the socket file descriptor in the provided pointer
  *sockfd = sfd;

  return 0;
}