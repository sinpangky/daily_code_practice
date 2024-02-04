#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 2);
  int fd;  // 文件描述符
  fd = open(argv[1], O_RDWR | O_CREAT);
  ERROR_CHECK(fd, -1, "open");
  char buf[1024] = {0};
  int len = read(fd, buf, sizeof(buf));
  printf("%s", buf);
  close(fd);

  return 0;
}
