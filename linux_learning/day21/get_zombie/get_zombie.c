#include <func.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  } else if (pid == 0) {
    // Child process
    printf("Child process\n");
    exit(0);
  } else {
    // Parent process
    while ((1));
    printf("Parent process\n");
    exit(0);
  }
}
