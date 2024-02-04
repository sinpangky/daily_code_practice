#include <func.h>

void daemon() {
  if (fork() != 0) {
    exit(0);
  }
  setsid();
  chdir("/");
  umask(0);
  for (int i = 0; i < 3; i++) {
    close(i);
  }
}

int main(int argc, char const *argv[]) {
  daemon();
  return 0;
}
