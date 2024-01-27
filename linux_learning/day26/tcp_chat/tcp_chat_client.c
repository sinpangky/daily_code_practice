#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int sock;

  struct sockaddr_in serv_address;
  memset(&serv_address, 0, sizeof(serv_address));
  serv_address.sin_family = AF_INET;
  serv_address.sin_addr.s_addr = inet_addr(argv[1]);
  serv_address.sin_port = htons(atoi(argv[2]));

  int addrlen = sizeof(serv_address);
  char buffer[1024] = {0};

  // 创建套接字
  sock = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sock, -1, "socket");

  // 连接到服务器
  int ret = connect(sock, (struct sockaddr *)&serv_address, addrlen);
  ERROR_CHECK(ret, -1, "connet");

  // 建立通信
  recv(sock, buffer, sizeof(buffer), 0);
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
      if(!strcmp(buffer,"exit\n")){
        break;
      }
      send(sock, buffer, strlen(buffer) - 1, 0);
    }
    if (FD_ISSET(sock, &set)) {
      memset(buffer, 0, sizeof(buffer));
      ret = recv(sock, buffer, sizeof(buffer), 0);
      if(0 ==ret) {
        break;
      }
      printf("Message from server:\n%s\n",buffer);
    }
  }
  // 关闭
  printf("------ Connection broke ------\n");
  close(sock);

  return 0;
}
