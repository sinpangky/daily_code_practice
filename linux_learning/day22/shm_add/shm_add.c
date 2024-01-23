#include <func.h>

int main(int argc, char const *argv[]) {
  int shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0);
  // initialize the shared memory
  p[0] = 0;
  if (!fork()) {
    // child process
    for (int i = 0; i < 10000000; i++) {
      p[0] += 1;
    }
    exit(0);
  } else {
    // parent process
    for (int i = 0; i < 10000000; i++) {
      p[0] += 1;
    }
    wait(NULL);
    printf("sum = %d\n", p[0]);
    exit(0);
  }
  shmdt(p);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
