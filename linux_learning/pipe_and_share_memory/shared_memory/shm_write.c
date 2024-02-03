#include <func.h>

int main(int argc, char const *argv[]) {
  key_t key = ftok(".", 200);
  // create a shared memory
  int shmid = shmget(key, 1024, IPC_CREAT | 0600);
  // attach the shared memory to the current process
  char *p = (char *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (char *)-1, "shmat");
  // write data to the shared memory
  strcpy(p, "How are you");
  // detach the shared memory from the current process
  shmdt(p);

  return 0;
}
