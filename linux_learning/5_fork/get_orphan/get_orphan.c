#include <func.h>

int main(int argc, char const *argv[]) {
  pid_t pid = fork();
  if (0 == pid) {
    while (1) {
      printf("I am child process, pid = %d\n", getpid());
      sleep(1);
    }
  } else {
    printf("I am parent process, pid = %d\n", getpid());
    sleep(1);
  }

  return 0;
}
