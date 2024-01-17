#include <unistd.h>
#include <stdio.h>

int main() {
  char path[1024];
  getcwd(path, sizeof(path));
  puts(path);
  int ret = chdir("../");
  if(0!=ret) {
    perror("chdir");
    return -1;
  }
  puts(getcwd(NULL, 0));

  return 0;
}