#include <func.h>

int main(int argc, char const *argv[])
{
  printf("当前进程PID：%d\n", getpid());
  printf("父进程PID：%d\n", getppid());
  printf("真实用户ID：%d\n", getuid());
  printf("真实组ID：%d\n", getgid());
  printf("有效用户ID：%d\n", geteuid());
  printf("有效组ID：%d\n", getegid());

  return 0;
}
