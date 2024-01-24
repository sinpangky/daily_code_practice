#include <func.h>

void sigfunc(int signum, siginfo_t *p, void *pp) {
  printf("signal %d begin...\n", signum);
  sleep(5);
  sigset_t pend;
  sigpending(&pend);
  if(sigismember(&pend,SIGQUIT)){
    printf("SIGQUIT is in pending queue.\n");
  }else {
    printf("SIGQUIT is not in pending queue.\n");
  }
  printf("signal %d begin...\n", signum);
}

int main(int argc, char const *argv[]) {
  struct sigaction mysigaction;
  memset(&mysigaction, 0, sizeof(mysigaction));
  mysigaction.sa_sigaction = sigfunc;
  mysigaction.sa_flags = SA_SIGINFO;
  // 屏蔽3号信号
  sigaddset(&mysigaction.sa_mask,SIGQUIT);
  int ret = sigaction(SIGINT,&mysigaction,NULL);
  ERROR_CHECK(ret , -1, "sigaction");
  while(1){
    sleep(1);
  }
  return 0;
}
