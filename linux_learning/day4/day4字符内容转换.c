// // hw1
// #include <stdio.h>
// #define MAXNUM 101
// int replaceSpaces(char* str) {
//   int i, spcaeCount = 0, previousLength = 0;
//   for (i = 0; str[i]; i++) {
//     if (str[i] == ' ') {
//       spcaeCount++;
//     }
//   }
//   previousLength = i;
//   if (previousLength + 3 * spcaeCount > MAXNUM) {
//     printf("字符串长度溢出，转换失败");
//     return 0;
//   }
//   for (; i > -1; i--) {
//     if (str[i] == ' ') {
//       str[i + 3 * spcaeCount] = '0';
//       str[i + 3 * spcaeCount - 1] = '2';
//       str[i + 3 * spcaeCount - 2] = '0';
//       str[i + 3 * spcaeCount - 3] = '%';
//       spcaeCount--;
//     } else {
//       str[i + 3 * spcaeCount] = str[i];
//     }
//   }

//   return 1;
// }

// int main() {
//   char sen[MAXNUM];
//   gets(sen);
//   replaceSpaces(sen);
//   puts(sen);
//   return 0;
// }

// hw2

#include <stdio.h>
// 将plus的值加到origin上
char* largeValuePlus(char* origin, char* plus) {
  int i, j, k, ntemp;
  char* temp;
  int flag = 0;
  // 遍历origin和plus取得各自位数
  for (i = 0; origin[i]; i++)
    ;
  for (j = 0; plus[j]; j++)
    ;
  // 若origin的位数小于plus，则将其进行对换
  if (i < j) {
    temp = origin;
    origin = plus;
    plus = temp;
    ntemp = i;
    i = j;
    j = ntemp;
  }
  i--;
  j--;
  // 从个位数开始相加,直到plus的最高位
  for (; j >= 0; j--) {
    if (origin[i] + plus[j] + flag > 9 + 2 * '0') {
      origin[i] = flag + origin[i] + plus[j] - 10 - '0';
      flag = 1;
      i--;
    } else {
      origin[i] = flag + origin[i] + plus[j] - '0';
      flag = 0;
      i--;
    }
  }
  // 直到origin的最高位
  for (; i >= 0; i--) {
    if (origin[i] + flag > 9 + '0') {
      origin[i] = flag + origin[i] - 10;
      flag = 1;
    } else {
      origin[i] = flag + origin[i];
      flag = 0;
    }
  }
  // 若总体的和产生了进位
  if (flag && i == -1) {
    for (k = 0; origin[k]; k++)
      ;
    for (k = 1; k >= 0; k--) {
      origin[k + 1] = origin[k];
    }
    origin[0] = '1';
  }
  return origin;
}

int main() {
  char first[52];
  char second[52];
  gets(first);
  gets(second);
  puts(largeValuePlus(first, second));

  return 0;
}