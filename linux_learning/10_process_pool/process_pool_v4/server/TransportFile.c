#include "head.h"

int SendFile(int client_fd) {
  // 1. get filename from client
#ifdef DEBUG
  printf("start SendFile\n");
#endif
  char content[1000] = {0};
  char filename[1000] = {0};
  int ret;
  // simulate the account directory
  strcpy(content, "/home/cpq/daily_code_practice/linux_learning/temp");
  ret = recv(client_fd, filename, sizeof(filename),0);
#ifdef DEBUG
  printf("%s\n", filename);
#endif
  if (ret <= 0) {
    return -1;
  }
  // fix the name, if client send only filename with out `/`, add `/` in front
  if (filename[0] != '/') {
    strcat(content, "/");
  }
  // find file in the complete directory
  strcat(content, filename);
#ifdef DEBUG
  printf("%s\n", content);
#endif
  if (access(content, F_OK) == -1) {
    printf("File not exist!\n");
    ret = -1;
    send(client_fd, &ret, sizeof(int), 0);
    return -1;
  } else {
    // send client the feed back. -1 for no file, 0 for existing.
    ret = 0;
#ifdef DEBUG
    printf("send file size\n");
#endif
    send(client_fd, &ret, sizeof(int), 0);

    // 2. open file
#ifdef DEBUG
    printf("start open file\n");
#endif
    int fd = open(content, O_RDONLY);
    ERROR_CHECK(fd, -1, "open");

    // 3. send content to client
    // send file size first
    struct stat file_buf;
    fstat(fd, &file_buf);
    long retval= sizeof(file_buf.st_size);
    memcpy(&retval, &file_buf.st_size, sizeof(file_buf.st_size));
    send(client_fd, &retval, sizeof(long), 0);
    // send file content
    long send_ret = sendfile(client_fd, fd, NULL, file_buf.st_size);
    ERROR_CHECK(send_ret, -1, "sendfile");

    // 4. close file descriptor
    close(fd);

    return 0;
  }
}