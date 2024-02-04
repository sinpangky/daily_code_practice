#include <func.h>

int main(int argc, char const *argv[])
{
  ARGS_CHECK(argc,2);
  // if file doesn't exist, create a new one; else, clean all content of the existing file
  int fd= open(argv[1],O_WRONLY);
  ERROR_CHECK(fd , -1,"open");
  int ret = ftruncate(fd,100);
  ERROR_CHECK(ret,-1,"ftruncate");
  return 0;
}
