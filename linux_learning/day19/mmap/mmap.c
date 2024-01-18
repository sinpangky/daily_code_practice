#include <func.h>

int main(int argc, char const* argv[]) {
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  char* p;
  // when use `mmap` cannot change the size of the file
  p = (char*)mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ERROR_CHECK(p, -1, "mmap");
  p[0] = 'H';
  p[1] = 'L';
  int ret = munmap(p, 10);
  ERROR_CHECK(ret, -1, "munmap");
  return 0;
}
