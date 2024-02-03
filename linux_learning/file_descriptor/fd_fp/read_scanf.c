#include <func.h>

int main(int argc, char const *argv[]) {
  char buf[1024] = {0};
  int ret = read(STDIN_FILENO, buf, sizeof(buf));
  ERROR_CHECK(ret,-1,"read");
  printf("%s", buf);

  return 0;
}
