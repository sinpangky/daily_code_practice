#include <func.h>

int main(int argc, char const *argv[])
{
  ARGS_CHECK(argc,2);
  // if file doesn't exist, create a new one; else, clean all content of the existing file
  int fd= open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0600);
  ERROR_CHECK(fd , -1,"open");
  printf("fd = %d\n"),fd;
  return 0;
}
