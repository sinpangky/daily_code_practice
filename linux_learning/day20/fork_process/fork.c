#include <func.h>

int main(int argc, char const *argv[])
{
  pid_t pid = fork();
  if (pid == 0) {
    // child process
    printf("I am child process, pid = %d\n", getpid());
    while(1);
  } else {
    // parent process
    printf("I am parent process, pid = %d\n", getpid());
    while(1);
  }

  return 0;
}
