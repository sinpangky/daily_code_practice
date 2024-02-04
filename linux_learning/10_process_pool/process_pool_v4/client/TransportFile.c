#include "head.h"

/** use "loop receive" to avoid the inconsistent client-recv and server-send
 * rates
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
/** receive the file from server
 * @param new_fd server_fd
 * @param filename char array of filename
 */
int ReceiveFile(int new_fd, char* filename) {
  off_t file_size;
  int ret = recvn(new_fd, (void*)&file_size, sizeof(off_t));
#ifdef DEBUG
  printf("recv file size\n");
#endif
  ERROR_CHECK(ret, -1, "recvn");
  // open or rewrite the file
  int fd = open(filename, O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");
  struct timeval start, end;
  gettimeofday(&start, NULL);
  // use pipe the transport file stream: server_fd -> pipe_fd[1]-> pipe_fd[0] -> file_fd
  int pipe_fd[2];
  pipe(pipe_fd);
  off_t total = 0;
  while (total < file_size) {
    off_t retval = splice(new_fd, NULL, pipe_fd[1], NULL, 4096, SPLICE_F_MORE);
    if (retval <= 0) {
      printf("Server break\n");
      break;
    }
    total += retval;
    retval = splice(pipe_fd[0], NULL, fd, NULL, retval, SPLICE_F_MORE);
    if (retval <= 0) {
      printf("the server break\n");
      break;
    }
  }
  printf("download finished\n");
  // print downloading time
  gettimeofday(&end, NULL);
  printf("download time = %ldus\n",
         (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
  close(pipe_fd[1]);
  close(pipe_fd[0]);
  close(fd);

  return 0;
}