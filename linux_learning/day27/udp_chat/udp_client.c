#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int sock;
  struct sockaddr_in serv_address;
  memset(&serv_address, 0, sizeof(serv_address));
  serv_address.sin_family = AF_INET;
  serv_address.sin_addr.s_addr = inet_addr(argv[1]);
  serv_address.sin_port = htons(atoi(argv[2]));

  char buffer[1024] = {0};

  // 创建 UDP 套接字
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  ERROR_CHECK(sock, -1, "socket");

  // 发送初始消息以建立通信
  sendto(sock, "Client Hello", strlen("Client Hello"), 0,
         (struct sockaddr *)&serv_address, sizeof(serv_address));
  recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
  // 成功建立连接
  if (!strcmp(buffer, "------ Connected with Server ------")) {
    printf("%s\n", buffer);
    fd_set set;
    while (1) {
      FD_ZERO(&set);
      FD_SET(STDIN_FILENO, &set);
      FD_SET(sock, &set);
      select(sock + 1, &set, NULL, NULL, NULL);
      if (FD_ISSET(STDIN_FILENO, &set)) {
        memset(buffer, 0, sizeof(buffer));
        read(STDIN_FILENO, buffer, sizeof(buffer));
        if (!strcmp(buffer, "exit\n")) {
          sendto(sock, buffer, strlen(buffer), 0,
                 (struct sockaddr *)&serv_address, sizeof(serv_address));
          break;
        }
        sendto(sock, buffer, strlen(buffer) - 1, 0,
               (struct sockaddr *)&serv_address, sizeof(serv_address));
      }
      if (FD_ISSET(sock, &set)) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        if (!strcmp(buffer, "exit\n")) {
          break;
        }
        printf("Message from server:\n%s\n\n", buffer);
      }
    }
  }
  // 关闭
  printf("------ Connection closed ------\n");
  close(sock);

  return 0;
}
