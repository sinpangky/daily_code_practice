#include <func.h>

int global_var = 10;  // Global variable

int main() {
  int stack_var = 20;  // Stack variable

  int *heap_var = (int *)malloc(sizeof(int));  // Heap variable
  *heap_var = 30;

  pid_t pid = fork();  // Create a child process

  int fd1 = open("file1", O_RDWR);

  if (pid == 0) {
    sleep(1);
    // Child process
    printf("Child Process:\n");
    printf("Global variable: %d, at %p\n", global_var, &global_var);
    printf("Stack variable: %d, at %p\n", stack_var, &stack_var);
    printf("Heap variable: %d, at %p\n", *heap_var, heap_var);
    printf("File descriptor: %d\n", fd1);

    global_var = 100;
    stack_var = 200;
    *heap_var = 300;

    int fd2 = open("file2", O_RDWR);
    printf("Modified values in child process:\n");
    printf("Global variable: %d, at %p\n", global_var, &global_var);
    printf("Stack variable: %d, at %p\n", stack_var, &stack_var);
    printf("Heap variable: %d, at %p\n", *heap_var, heap_var);
    printf("File descriptor inside: %d\n", fd2);
  } else if (pid > 0) {
    // Parent process
    printf("Parent Process:\n");
    int fd2 = open("file2", O_RDWR);
    printf("Global variable: %d, at %p\n", global_var, &global_var);
    printf("Stack variable: %d, at %p\n", stack_var, &stack_var);
    printf("Heap variable: %d, at %p\n", *heap_var, heap_var);
    printf("File descriptor: %d\n", fd1);
    printf("File descriptor inside: %d\n", fd2);
  } else {
    // Fork failed
    fprintf(stderr, "Fork failed\n");
    return -1;
  }

  free(heap_var);  // Free the heap variable

  return 0;
}
