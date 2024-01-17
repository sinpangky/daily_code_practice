#include <stdio.h>

#define LENGTH1 9
#define LENGTH2 19

// homework 1
void homework1() {
  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < i + 1; j++) {
      printf("%d X %d = %-2d  ", i, j, i * j);
    }
    printf("\n");
  }
}

// homework 2_1
void homework2_1() {
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < LENGTH1; j++) {
      if (i % 2 != j % 2 && i + j > 4 && i + j < 14 && i - j > -4 &&
          i - j < 6)  // 在4条边界线的范围之内的、不相邻的点打印
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}

// homework 2_2
void homework2_2() {
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < LENGTH1; j++) {
      if (i > 0 && i < 10 &&
          (i + j == 5 || i + j == 13 || i - j == -3 ||
           i - j == 5))  // 在四条边线上的点打印
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}

// homework 2_3
void homework2_3() {
  // 对上半段的讨论
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < LENGTH2; j++) {
      // 简洁版：
      // if(i>0 && i%2 == j%2 && ((i+j>3 &&i-j>-5)||(i+j>13 &&i-j>-15)))
      //   printf("*");
      // else
      //   printf(" ");
      if (i > 0 && i % 2 == j % 2)  // 保证点不相邻
        if ((i + j > 3 && i - j > -5) ||
            (i + j > 13 && i - j > -15))  // 保证边线范围内
          printf("*");
        else
          printf(" ");
      else
        printf(" ");
    }
    printf("\n");
  }
  for (int i = 4; i < 14; i++) {
    for (int j = 0; j < LENGTH2; j++) {
      if (i % 2 == j % 2 && i - j < 5 && i + j < 23)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}

int main() {
  homework1();
  printf("\n");
  homework2_1();
  printf("\n");
  homework2_2();
  printf("\n");
  homework2_3();
  return 0;
}
