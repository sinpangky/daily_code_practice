#include <func.h>

int main(int argc, char const *argv[]) {
  int fd;
  fd = open("file", O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  struct stat buf;
  int ret = fstat(fd, &buf);
  ERROR_CHECK(ret, -1, "fstat");
  printf("size = %ld", buf.st_size);

  return 0;
}
