#include <func.h>

int main(int argc, char const *argv[]) {
  int fdw = open(argv[1], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");
  int fdr = open(argv[2], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");
  printf("fdr = %d, fdw = %d -- Conversion Begins\n", fdr, fdw);
  char buf[1024] = {0};
  while (1) {
    // read the 2.pipe
    memset(buf, 0, sizeof(buf));
    read(fdr, buf, sizeof(buf));
    printf("chat1: %s", buf);
    if (!strcmp(buf, "exit\n")) {
      break;
    }
    // read the STDIN
    memset(buf, 0, sizeof(buf));
    read(STDIN_FILENO, buf, sizeof(buf));
    // send to 1.pipe
    write(fdw, buf, strlen(buf));
    
  }
  return 0;
}
