#include <func.h>

void sigfunc(int signum, siginfo_t *p, void *pp) {
  printf("Received signal %d\n", signum);
}

int main(int argc, char const *argv[]) {
  struct sigaction mysigaction;
  memset(&mysigaction, 0, sizeof(mysigaction));
  mysigaction.sa_sigaction = sigfunc;
  mysigaction.sa_flags = SA_SIGINFO | SA_RESTART;
  int ret = sigaction(SIGINT,&mysigaction,NULL);
  ERROR_CHECK(ret , -1, "sigaction");
  char buf[100];
  read(STDIN_FILENO,buf,sizeof(buf));
  puts(buf);
  return 0;
}
