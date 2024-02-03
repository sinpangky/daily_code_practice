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
  ret = listen(server_fd,3);
  ERROR_CHECK(ret,-1,"listen");
  
  // 接受连接
  new_socket = accept(server_fd,(struct sockaddr* )&address,(socklen_t*)&addrlen);
  ERROR_CHECK(new_socket,-1,"accept");

  send(new_socket, hello, strlen(hello), 0);
  printf("------ Connected with Client ------\n");

  // 读取客户端发送的数据
  memset(buffer,0,sizeof(buffer));
  recv(new_socket,buffer,sizeof(buffer),0);
  printf("Message from client:\n%s\n",buffer);

  // 回复客户端
  memset(buffer,0,sizeof(buffer));
  strcpy(buffer,"hello, I'm SERVER.");
  send(new_socket,buffer,sizeof(buffer),0);

  // 关闭
  close(new_socket);
  close(server_fd);

  return 0;
}
