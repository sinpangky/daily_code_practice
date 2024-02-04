#include <func.h>

int main(int argc, char const *argv[]) {
  key_t key = ftok(".", 200);
  // get a shared memory
  int shmid = shmget(key, 1024, 0600);
  // attach the shared memory to the current process
  char *p = (char *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (char *)-1, "shmat");
  // read data from the shared memory
  puts(p);
  // detach the shared memory from the current process
  shmdt(p);
  // delete the shared memory
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}