// // hw1
// #include <stdio.h>
// void mystrcpy(char* to, const char* from) {
//   int count = 0;
//   while (from[count]) {
//     to[count] = from[count];
//     count++;
//   }
//   to[count] = 0;
// }
// int mystrcmp(const char* a, const char* b) {
//   int count = 0;
//   // 遍历
//   while (a[count] && b[count]) {
//     if (a[count] == b[count]) {
//       count++;  // 相同则比较下一个
//     } else {
//       return a[count] - b[count];  // 不同则输出当前比较字符的差
//     }
//   }
//   // 遍历完的三种情况
//   if (a[count] == 0 && b[count] == 0) {  // a、b相同
//     return 0;
//   } else if (a[count]) {  // a不空，b空
//     return a[count];
//   } else {
//     return -b[count];  // b不空，a空
//   }
// }
// void mystrcat(char* to, char* from) {
//   int i = 0;
//   int count = 0;
//   while (to[count]) {
//     count++;
//   }
//   while (from[i]) {
//     to[count + i] = from[i];
//     i++;
//   }
//   to[count + i] = 0;
// }
// int mystrlen(char* a) {
//   int count = 0;
//   while (a[count]) {
//     count++;
//   }
//   return count;
// }
// int main() {
//   char a[20] = "hello";
//   char b[20] = "hello1";
//   puts(a);
//   mystrcpy(a, b);
//   mystrcat(a,b);
//   printf("%d\n",mystrlen(a));
//   puts(a);
//   return 0;
// }

// hw2
#include <stdio.h>
int main() {
  char a[100];
  fgets(a, 100, stdin);
  int i = 0;
  int count = 0;
  while (a[i] != '\n') {
    if (a[i] == ' ') {
      i++;
    } else {
      while (a[i] != ' ' && a[i] != '\n') {
        i++;
      }
      count++;
    }
  }
  printf("%d", count);
  return 0;
}

// // hw3
// #include <stdio.h>
// #include <string.h>
// int main() {
//   char a[100];
//   char temp[100]={0};
//   fgets(a, 100, stdin);
//   int i = 0;
//   while (a[i] != '\n') {
//     if (a[i] == ' ') {
//       i++;
//     } else {
//       if (a[i + 1] == ' ' || a[i + 1] == '\n') {
//         strncat(temp,&a[i],1);
//         printf("%s\n",temp);
//         temp[0] = 0;
//         i++;
//       } else {
//         strncat(temp,&a[i],1);
//         i++;
//       }
//     }
//   }
//   return 0;
// }

// // hw4
#include <stdio.h>
#include <string.h>
// void print(char* pstr){
//   int i =0;
//   while (pstr[i]){
//     putchar(pstr[i]);
//     i++;
//   }
// }
// // 实现方式1
// void sentenceTurnOver(char* sentence) {
//   int i = 0;
//   char temp[20] = {0};
//   if (sentence[i] == '\n') {
//     return;
//   } else if (sentence[i] == ' ') {
//     while (sentence[i] == ' ') {
//       strncat(temp, &sentence[i], 1);
//       i++;
//     }
//     sentenceTurnOver(&sentence[i]);
//     print(temp);
//   } else {
//     while (sentence[i] != ' ' && sentence[i] != '\n') {
//       strncat(temp, &sentence[i], 1);
//       i++;
//     }
//     sentenceTurnOver(&sentence[i]);
//     print(temp);
//   }
// }

// // 可忽略
// // 实现方式2
// void reverseStr(char* str, int head, int tail) {
//   char temp;
//   for (int i = 0; i <= (tail - head) / 2; i++) {
//     temp = str[head + i];
//     str[head + i] = str[tail - i];
//     str[tail - i] = temp;
//   }
// }
// void sentenceTurnOver(char* a){
//   // 翻转整个字符串
//   reverseStr(a,0,strlen(a)-1);
//   // 遍历找到每一个单词
//   int i=0;
//   int pre;
//   while (a[i])
//   {
//     if(a[i]== ' ') {
//       i++;
//     } else
//   }
// }
// int main() {
//   char a[100];
//   fgets(a, 100, stdin);
//   sentenceTurnOver(a);
//   return 0;
// }