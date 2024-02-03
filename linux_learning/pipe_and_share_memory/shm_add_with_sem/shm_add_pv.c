#include <func.h>

int main(int argc, char const *argv[]) {
  int shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0);
  // initialize the shared memory
  p[0] = 0;
  key_t key = ftok(".", 200);
  // create a semaphore
  int sem_id = semget(key, 1, IPC_CREAT | 0600);
  ERROR_CHECK(sem_id, -1, "semget");
  // initialize the semaphore
  int ret = semctl(sem_id, 0, SETVAL, 1);
  ERROR_CHECK(ret, -1, "semctl");
  struct sembuf p_op;
  struct sembuf v_op;
  p_op.sem_num = 0;
  p_op.sem_op = -1;
  p_op.sem_flg = SEM_UNDO;
  v_op.sem_num = 0;
  v_op.sem_op = 1;
  v_op.sem_flg = SEM_UNDO;

  if (!fork()) {
    // child process
    for (int i = 0; i < 1000000; i++) {
      semop(sem_id, &p_op, 1);
      p[0] += 1;
      semop(sem_id, &v_op, 1);
    }
    exit(0);
  } else {
    // parent process
    for (int i = 0; i < 1000000; i++) {
      semop(sem_id, &p_op, 1);
      p[0] += 1;
      semop(sem_id, &v_op, 1);
    }
    wait(NULL);
    printf("sum = %d\n", p[0]);
    exit(0);
  }
  shmdt(p);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
