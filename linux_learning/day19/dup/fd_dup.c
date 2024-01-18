#include <func.h>

int main(int argc, char const *argv[]) {
  int fd = open("file1", O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  int fd_2 = dup(fd);
  printf("fd = %d, fd_2 = %d\n", fd, fd_2);
  close(fd);
  char buf[1024] = {0};
  int ret = read(fd_2,buf,sizeof(buf));
  ERROR_CHECK(ret, -1,"read");
  printf("%s",buf);

  return 0;
}
