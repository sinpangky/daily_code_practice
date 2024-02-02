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
  printf("Please input filename to download:\n");
  fflush(stdout);
  fd_set readfds;
  struct timeval tv;
  int retval;
  tv.tv_sec = 10;
  tv.tv_usec = 0;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);
  retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
  if (retval == 0) {
    printf("No input within 10s\n");
    return 1;
  } else{
    scanf("%s", buf);
  }
  send(new_fd, buf, strlen(buf), 0);
  recv(new_fd, &recv_length, sizeof(int), 0);
  if (-1 == recv_length) {
    printf("File not exist!\n");
    return -1;
  }

  int fd = open(buf, O_RDWR | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");

  off_t file_size;
  recvn(new_fd, &recv_length, 4);
  recvn(new_fd, &file_size, recv_length);
  struct timeval start, end;
  gettimeofday(&start, NULL);

  int ret = ftruncate(fd,file_size);
  ERROR_CHECK(ret , -1,"ftruncate");
  char *p = (char*)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  ERROR_CHECK(p,(char*)-1,"mmap");
  recvn(new_fd,p,file_size);
  ret =  munmap(p,file_size);
  ERROR_CHECK(ret ,-1,"munmap");

  // while (file_size - download_size > 1000) {
  //   recvn(new_fd, &buf, 1000);
  //   write(fd, buf, 1000);
  //   download_size += 1000;
  //   if (download_size - last_size >= slice) {
  //     printf("%2ld%%\r", 100 * download_size / file_size);
  //     fflush(stdout);
  //     last_size = download_size;
  //   }
  // }
  // // receive the remaining file block
  // recvn(new_fd, &buf, file_size - download_size);
  // write(fd, buf, file_size - download_size);
  
  printf("download finished\n");
  // print used time
  gettimeofday(&end, NULL);
  printf("download time = %ldus\n",
         (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

  close(fd);
  return 0;
}