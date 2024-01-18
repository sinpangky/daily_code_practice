#include <func.h>

int main(int argc, char const *argv[]) {
  ARGS_CHECK(argc, 3);
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");
  int fdw = open(argv[2], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");
  printf(
      "fdr = %d, fdw = %d -- Conversation Begins\n(use `ctrl + d` to exit)\n",
      fdr, fdw);
  char buf[1024] = {0};
  int ret = 0;
  fd_set readset;
  while (1) {
    // clear readset
    FD_ZERO(&readset);
    // use select to minitor STDIN and fdr
    FD_SET(STDIN_FILENO, &readset);
    FD_SET(fdr, &readset);
    int fd_ready_num = select(fdr + 1, &readset, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &readset)) {
      // read the STDIN
      memset(buf, 0, sizeof(buf));
      ret = read(STDIN_FILENO, buf, sizeof(buf));
      if (0 == ret) {
        printf("You break this conversation\n");
        break;
      }
      // send to 2.pipe
      write(fdw, buf, strlen(buf));
    }
    if (FD_ISSET(fdr, &readset)) {
      // read the 1.pipe
      memset(buf, 0, sizeof(buf));
      int ret = read(fdr, buf, sizeof(buf));
      ERROR_CHECK(fdr, -1, "read");
      if (0 == ret) {
        printf("Conversation is broken by the opposite.\n");
        break;
      }
      printf("chat2: %s", buf);
    }
  }
  return 0;
}
