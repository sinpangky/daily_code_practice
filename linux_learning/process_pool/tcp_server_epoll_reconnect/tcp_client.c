#include <func.h>
#include <sys/ioctl.h>

void printRightAligned(char* message) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int i = strlen(message) - 1;
  message[i] = 0;
  int padding = w.ws_col - i;  // 计算右对齐所需的空格数量
  if (padding < 0) padding = 0;

  printf("\033[A\033[2K");  // 先上移光标一行，然后清除该行
  printf("%*s%s\n", padding, "", message);  // 输出右对齐的消息
}

int main(int argc, char const* argv[]) {
  int sock;

  struct sockaddr_in serv_address;
  memset(&serv_address, 0, sizeof(serv_address));
  serv_address.sin_family = AF_INET;
  serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_address.sin_port = htons(7234);

  int addrlen = sizeof(serv_address);
  char buffer[1024] = {0};

  // 创建套接字
  sock = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sock, -1, "socket");

  // 连接到服务器
  int ret = connect(sock, (struct sockaddr*)&serv_address, addrlen);
  ERROR_CHECK(ret, -1, "connet");

  // 建立通信
  fd_set set;

  while (1) {
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    FD_SET(sock, &set);
    select(sock + 1, &set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &set)) {
      memset(buffer, 0, sizeof(buffer));
      read(STDIN_FILENO, buffer, sizeof(buffer));
      printRightAligned(buffer);
      if (!strcmp(buffer, "exit")) {
        break;
      }
      send(sock, buffer, strlen(buffer), 0);
    }
    if (FD_ISSET(sock, &set)) {
      memset(buffer, 0, sizeof(buffer));
      ret = recv(sock, buffer, sizeof(buffer), 0);
      if (0 == ret) {
        break;
      }
      printf("%s\n", buffer);
    }
  }
  // 关闭
  printf("------ Connection broke ------\n");
  close(sock);

  return 0;
}
