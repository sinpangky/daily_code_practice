#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int server_fd, new_socket;
  struct sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(argv[1]);
  address.sin_port = htons(atoi(argv[2]));
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  char *hello = "------ Connected with Server ------";

  // 创建套接字
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(server_fd, -1, "socket");

  // 绑定套接字
  int ret = bind(server_fd, (struct sockaddr *)&address, addrlen);
  ERROR_CHECK(ret, -1, "bind");

  // 监听连接
  ret = listen(server_fd, 3);
  ERROR_CHECK(ret, -1, "listen");

  // 接受连接
  new_socket =
      accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  ERROR_CHECK(new_socket, -1, "accept");

  send(new_socket, hello, strlen(hello), 0);
  printf("------ Connected with Client ------\n");
  fd_set set;

  while (1) {
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    FD_SET(new_socket, &set);
    select(new_socket + 1, &set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &set)) {
      memset(buffer, 0, sizeof(buffer));
      read(STDIN_FILENO, buffer, sizeof(buffer));
      if (!strcmp(buffer, "exit\n")) {
        break;
      }
      send(new_socket, buffer, strlen(buffer) - 1, 0);
    }
    if (FD_ISSET(new_socket, &set)) {
      memset(buffer, 0, sizeof(buffer));
      ret = recv(new_socket, buffer, sizeof(buffer), 0);
      if (0 == ret) {
        break;
      }
      printf("Message from client:\n%s\n", buffer);
    }
  }
  // 关闭
  printf("------ Connection broke ------\n");
  close(new_socket);
  close(server_fd);

  return 0;
}
