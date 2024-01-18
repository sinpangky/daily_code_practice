#include <func.h>

void mode_to_permission(mode_t st_mode, char* permission) {
  // 去掉前三位，只取后九位
  st_mode &= 0777;
  char perms[] = "rwxrwxrwx";
  int i;
  for (i = 0; i < 9; i++) {
    // 按位与
    if (!(st_mode & (1 << (8 - i)))) {
      perms[i] = '-';
    }
  }
  strcpy(permission, perms);
}

int main(int argc, char* argv[]) {
  // 检查参数
  ARGS_CHECK(argc, 2);
  DIR* dir;
  // 去到给定的目录
  int ret = chdir(argv[1]);
  ERROR_CHECK(ret, -1, "chdir");
  // 打开目录
  dir = opendir(".");
  ERROR_CHECK(dir, NULL, "opendir");
  struct dirent* p;
  // 获取目录中文件名
  while (p = readdir(dir)) {
    // 跳过`.`和`..`
    if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
      continue;
    }
    // 读取文件信息
    struct stat buf;
    int ret_tmp = stat(p->d_name, &buf);
    ERROR_CHECK(ret_tmp, -1, "stat");
    // stat中的信息变为希望的格式
    // 得到指定格式"%b %d %H:%M:%S"的最后修改时间
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%b %d %H:%M:%S",
             gmtime(&(buf.st_mtime)));
    // 得到指定格式的权限
    char permission[20];
    mode_to_permission(buf.st_mode, permission);
    printf("-%s %u %s %s %7ld %s %s\n", permission, buf.st_nlink,
           getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name,
           buf.st_size, time_string, p->d_name);
  }
  closedir(dir);
  return 0;
}