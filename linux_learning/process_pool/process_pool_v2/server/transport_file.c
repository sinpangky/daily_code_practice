#include "head.h"

int SendFile(int client_fd) {
  // 1. send filename
  FileToTrans t;
  printf("please input your filename:\n");
  scanf("%s", t.content);
  t.size = strlen(t.content);
  send(client_fd, &t, 4 + t.size, 0);
  // 2. open file
  int fd = open(t.content, O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  // 3. send to client
  struct stat file_buf;
  fstat(fd, &file_buf);
  t.size = sizeof(file_buf.st_size);
  memcpy(t.content, &file_buf.st_size, sizeof(file_buf.st_size));
  send(client_fd, &t, 4 + t.size, 0);  // send file size first
  int ret;

  while ((t.size = read(fd, t.content, sizeof(t.content)))) {
    ret = send(client_fd, t.content, t.size, 0);
    if (-1 == ret) {  // if connection break
      printf("Connection break during downloading\n");
      goto END;
    }
  }
  printf("File transport succeed\n");
END:
  close(fd);
  return 0;
}

int recvn(int new_fd, void* startPtr, int length) {
  int total = 0, ret;
  char* p = (char*)startPtr;
  while (total < length) {
    ret = recv(new_fd, p + total, length - total, 0);
    ERROR_CHECK(ret, -1, "recv");
    if (0 == ret) {
      return -1;
    }
    total += ret;
  }
  return 0;
}

int ReceiveFile(int new_fd) {
  int recv_length;
  char buf[1000] = {0};
  recvn(new_fd, &recv_length, 4);
  recvn(new_fd, buf, recv_length);
  printf("buf = %s\n", buf);
  int fd = open(buf, O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");

  while (1) {
    recvn(new_fd, &recv_length, 4);
    if (recv_length) {
      recvn(new_fd, buf, recv_length);
      write(fd, buf, recv_length);
    } else {
      break;
    }
  }
  close(fd);
  return 0;
}