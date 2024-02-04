#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 1);
  int fd = open("file", O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  char buf[1024] = {0};
  off_t offset = lseek(fd, 11, SEEK_SET);
  ERROR_CHECK(offset, -1, "lseek");
  printf("offset = %ld\n", offset);
  // fd has been at the 11th positon
  int ret = read(fd, buf, sizeof(buf));
  ERROR_CHECK(ret, -1, "read");
  puts(buf);
  ret = write(fd, "howareyou", 9);
  ERROR_CHECK(ret, -1, "write");
  return 0;
}
