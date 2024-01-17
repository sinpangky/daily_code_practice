#include <func.h>

int tree(char* path, int depth) {
  DIR* dir;
  dir = opendir(path);
  ERROR_CHECK(dir, NULL, "opendir");
  struct dirent* p;
  while (p = readdir(dir)) {
    if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
      continue;
    }
    for (int i = 0; i < depth*2; i++)
    {
      printf("——");
    }
    printf("%s\n",  p->d_name);
    if (p->d_type == 4) {
      char new_path[1024] = {0};
      sprintf(new_path, "%s/%s", path, p->d_name);
      tree(new_path, depth +1);
    }
  }
  closedir(dir);
  return 0;
}

int main(int argc, char* argv[]) {
  ARGS_CHECK(argc, 2);
  tree(argv[1], 0);
  return 0;
}