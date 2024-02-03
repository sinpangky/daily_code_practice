#include "head.h"
/** use "loop receive" to avoid the inconsistent client-recv and server-send rates
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

int ReceiveFile(int new_fd, char* fileinput) {
  int recv_length;
  send(new_fd, fileinput, strlen(fileinput), 0);
  recvn(new_fd, &recv_length, sizeof(int));
  if (-1 == recv_length) {
    printf("File not exist!\n");
    return -1;
  }

  int fd = open(fileinput, O_RDWR | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");

  off_t file_size;
  recvn(new_fd, &recv_length, 4);
  recvn(new_fd, &file_size, recv_length);
  struct timeval start, end;
  gettimeofday(&start, NULL);

  int ret = ftruncate(fd, file_size);
  ERROR_CHECK(ret, -1, "ftruncate");
  char* p =
      (char*)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ERROR_CHECK(p, (char*)-1, "mmap");
  recvn(new_fd, p, file_size);
  ret = munmap(p, file_size);
  ERROR_CHECK(ret, -1, "munmap");

  printf("download finished\n");
  // print used time
  gettimeofday(&end, NULL);
  printf("download time = %ldus\n",
         (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

  close(fd);
  return 0;
}