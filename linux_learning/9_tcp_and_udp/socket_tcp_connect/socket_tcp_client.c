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

  // 回复客户端
  memset(buffer, 0, sizeof(buffer));
  strcpy(buffer, "hello, I'm CLIENT.");
  send(sock, buffer, sizeof(buffer), 0);

    // 读取客户端发送的数据
  memset(buffer, 0, sizeof(buffer));
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Message from server:\n%s\n", buffer);

  // 关闭
  close(sock);

  return 0;
}
