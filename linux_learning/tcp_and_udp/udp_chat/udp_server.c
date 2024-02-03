#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int server_fd;
  struct sockaddr_in address, client_addr;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(argv[1]);
  address.sin_port = htons(atoi(argv[2]));
  char buffer[1024] = {0};
  char *hello = "------ Connected with Server ------";

  // 创建 UDP 套接字
  server_fd = socket(AF_INET, SOCK_DGRAM, 0);
  ERROR_CHECK(server_fd, -1, "socket");

  // 绑定套接字
  int ret = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  ERROR_CHECK(ret, -1, "bind");

  // 发送初始消息给客户端
  int client_len = sizeof(client_addr);
  recvfrom(server_fd, buffer, sizeof(buffer), 0,
           (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
  if (!strcmp(buffer, "Client Hello")) {
    sendto(server_fd, hello, strlen(hello), 0, (struct sockaddr *)&client_addr,
           client_len);
    printf("------ Connected with Client ------\n");

    fd_set set;
    while (1) {
      FD_ZERO(&set);
      FD_SET(STDIN_FILENO, &set);
      FD_SET(server_fd, &set);
      select(server_fd + 1, &set, NULL, NULL, NULL);
      if (FD_ISSET(STDIN_FILENO, &set)) {
        memset(buffer, 0, sizeof(buffer));
        read(STDIN_FILENO, buffer, sizeof(buffer));
        if (!strcmp(buffer, "exit\n")) {
          sendto(server_fd, buffer, strlen(buffer), 0,
                 (struct sockaddr *)&client_addr, sizeof(client_addr));
          break;
        }
        sendto(server_fd, buffer, strlen(buffer) - 1, 0,
               (struct sockaddr *)&client_addr, sizeof(client_addr));
      }
      if (FD_ISSET(server_fd, &set)) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server_fd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (!strcmp(buffer, "exit\n")) {
          break;
        }
        printf("Message from client:\n%s\n\n", buffer);
      }
    }
  }
  // 关闭
  printf("------ Connection closed ------\n");
  close(server_fd);

  return 0;
}