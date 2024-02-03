#include "head.h"

int SendFile(int client_fd) {
  // 1. get filename from client
  FileToTrans t;
  int ret;
  t.size = -1;
  // simulate the account directory
  strcpy(t.content, "/home/cpq/daily_code_practice/linux_learning/temp");
  char filename[100] = {0};
  // wait at most 2s for the filename coming
  struct timeval tv;
  tv.tv_sec = 2;
  tv.tv_usec = 0;
  setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
  ret = recv(client_fd, filename, sizeof(filename), 0);
  if (ret ==0){
    return -1;
  }
  // fix the name, if client send only filename with out `/`, add `/` in front
  if(filename[0] !=  '/'){
    strcat(t.content, '/');
  }
  // find file in the complete directory
  strcat(t.content, filename);  
  if (access(t.content, F_OK) == -1) {
    printf("File not exist!\n");
    send(client_fd, &t.size, sizeof(int), 0);
    return -1;
  }
  // send client the feed back. -1 for no file, 0 for existing.
  t.size = 0;
  send(client_fd, &t.size, sizeof(int), 0);
  t.size = strlen(filename);

  // 2. open file
  int fd = open(t.content, O_RDONLY);
  ERROR_CHECK(fd, -1, "open");

  // 3. send content to client
  // send file size first
  struct stat file_buf;
  fstat(fd, &file_buf);
  t.size = sizeof(file_buf.st_size);
  memcpy(t.content, &file_buf.st_size, sizeof(file_buf.st_size));
  send(client_fd, &t, 4 + t.size, 0);
  // send file content
  char* p = (char* )mmap(NULL,file_buf.st_size,PROT_READ,MAP_SHARED,fd,0);
  ERROR_CHECK(p,(char*)-1,"mmap");
  long send_ret = send(client_fd,p,file_buf.st_size,0);
  if(send_ret == -1){
    printf("Connection break during downloading\n");
      goto END;
  }
  printf("File transport succeed\n");
  munmap(p,file_buf.st_size);

  // 4. close file descriptor
END:
  close(fd);
  return 0;
}
/** use "loop-receive" to avoid the inconsistent client-recv and server-send rates
*/
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