#include <func.h>

void sigfunc(int signum, siginfo_t *p, void *pp) {
  printf("pid = %d, uid = %d\n",p->si_pid,p->si_uid);
}

int main(int argc, char const *argv[]) {
  struct sigaction mysigaction;
  memset(&mysigaction, 0, sizeof(mysigaction));
  mysigaction.sa_sigaction = sigfunc;
  mysigaction.sa_flags = SA_SIGINFO | SA_RESETHAND;
  int ret = sigaction(SIGINT,&mysigaction,NULL);
  ERROR_CHECK(ret , -1, "sigaction");
  while(1){
    sleep(1);
  }
  return 0;
}
