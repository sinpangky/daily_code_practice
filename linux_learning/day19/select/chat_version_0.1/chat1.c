#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");
  int fdw = open(argv[2], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");
  printf("fdr = %d, fdw = %d -- Conversion Begins\n", fdr, fdw);
  char buf[1024] = {0};
  while (1) {
    // read the STDIN
    memset(buf, 0, sizeof(buf));
    read(STDIN_FILENO, buf, sizeof(buf));
    // send to 2.pipe
    write(fdw, buf, strlen(buf));
    // read the 1.pipe
    memset(buf, 0, sizeof(buf));
    int ret = read(fdr, buf, sizeof(buf));
    ERROR_CHECK(fdr, -1, "read");
    printf("chat2: %s", buf);
    // receive the end signal as "exit\n"
    if (!strcmp(buf, "exit\n")) {
      break;
    }
  }

  return 0;
}
