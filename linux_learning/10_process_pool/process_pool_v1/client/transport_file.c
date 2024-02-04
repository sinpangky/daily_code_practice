#include "head.h"

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

  off_t file_size;
  recvn(new_fd,&recv_length,4);
  recvn(new_fd,&file_size,recv_length);
  off_t download_size =0;
  off_t last_slice =0;
  off_t slice = file_size/100;

  while (1) {
    recvn(new_fd, &recv_length, 4);
    download_size+=recv_length;
    if(download_size - last_slice>=slice){
      printf("%3.0lf%%\r",100.0*download_size/file_size);
      fflush(stdout);
      last_slice = download_size;
    }
    if (recv_length) {
      recvn(new_fd, buf, recv_length);
      write(fd, buf, recv_length);
    } else {
      printf("100%%\n");
      break;
    }
  }
  close(fd);
  return 0;
}