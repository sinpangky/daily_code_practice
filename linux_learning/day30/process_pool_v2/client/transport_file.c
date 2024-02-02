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
  printf("file = %s\n", buf);
  int fd = open(buf, O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");

  off_t file_size;
  recvn(new_fd, &recv_length, 4);
  recvn(new_fd, &file_size, recv_length);
  off_t download_size = 0;
  off_t last_size = 0;
  off_t slice = file_size / 100;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  printf("  0%%\r");
  while (file_size - download_size > 1000) {
    recvn(new_fd, &buf, 1000);
    write(fd, buf, 1000);
    download_size += 1000;
    if (download_size - last_size >= slice) {
      printf("%2ld%%\r", 100 * download_size / file_size);
      fflush(stdout);
      last_size = download_size;
    }
  }
  // receive the remaining file block
  recvn(new_fd, &buf, file_size - download_size);
  write(fd, buf, file_size - download_size);
  printf("100%%\n");
  // print used time
  gettimeofday(&end, NULL);
  printf("download time = %ldus\n",
         (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

  close(fd);
  return 0;
}