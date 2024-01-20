#include <func.h>

int main(int argc, char const *argv[])
{
  ARGS_CHECK(argc, 2);
  int fd;
  fd = open(argv[1], O_WRONLY | O_CREAT, 0664);
  ERROR_CHECK(fd, -1, "open");

  write(fd, "hello", 5);
  close(fd);

  return 0;
}
