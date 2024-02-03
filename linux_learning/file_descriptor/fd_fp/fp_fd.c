#include <func.h>

int main(int argc, char const *argv[])
{
  FILE* fp= fopen("Makefile","r");
  ERROR_CHECK(fp,NULL,"fopen");
  int fd = fileno(fp);
  char buf[1024]={0};
  int ret = read(fd,buf,sizeof(buf));
  ERROR_CHECK(ret, -1, "read");
  puts(buf);

  return 0;
}
