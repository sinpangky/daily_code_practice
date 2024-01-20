#include <func.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  } else if (pid == 0) {
    // Child process
    printf("Child process\n");
    int *p = NULL;
    *p = 134;
    exit(0);
  } else {
    // Parent process
    sleep(1);
    printf("Parent process\n");
    int status;
    pid_t child =wait(&status);  // Collect the exit status of the child process
    if (WIFEXITED(status)) {
      printf("Child process exit code: %d\n", WEXITSTATUS(status));
    } else {
      printf("Child process crashed. Signal: %d\n", WTERMSIG(status));
    } 
    printf("Child process pid: %d\n", child);
    exit(0);
  }
}
