#include <stdio.h>
#include <stdlib.h>
void change(char* ptr) {
  ptr[1] = 'n';  // 操作非法，编译错误，提示 error C2166: 左值指定 const 对象
}

int main() {
  char str[] = "hello world";
  const char* ptr = str;
  str[0] = 'H';  // 操作合法 puts(ptr);
  // ptr[1] = 'n';  // 操作非法，编译错误，提示 error C2166: 左值指定 const 对象
  change(ptr);
  puts(ptr);
  system("pause");
}


