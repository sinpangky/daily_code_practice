#include <func.h>

int main(int argc, char const *argv[])
{
  ARGS_CHECK(argc,2);
   // if file doesn't exist, create one; else, error report "open" fail.
  int fd= open(argv[1],O_RDWR|O_CREAT|O_EXCL,0600);
  ERROR_CHECK(fd , -1,"open");
  printf("fd = %d\n",fd);
  return 0;
}
