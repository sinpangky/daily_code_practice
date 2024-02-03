#include <func.h>

int main(int argc, char* argv[]) {
  ARGS_CHECK(argc, 2);
  int ret;
  struct stat buf;
  ret = stat(argv[1], &buf);
  ERROR_CHECK(ret, -1, "stat");
  printf("inode=%lu,mode=%x,nlink=%u,user=%s,size=%ld,time=%s\n", buf.st_ino,
         buf.st_mode, buf.st_nlink, getpwuid(buf.st_uid)->pw_name, buf.st_size,
         ctime(&buf.st_mtime) + 4);

  return 0;
}