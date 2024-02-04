#include <func.h>

int main(int argc, char const *argv[]) {
  int pp[2];
  pipe(pp);

  if (!fork()) {
    // child process
    close(pp[0]);
    write(pp[1], "hello", 6);
    close(pp[1]);
    exit(0);
  } else {
    // parent process
    close(pp[1]);
    char buf[10];
    wait(NULL);
    read(pp[0], buf, sizeof(buf));
    close(pp[0]);
    puts(buf);
    exit(0);
  }
  return 0;
}
