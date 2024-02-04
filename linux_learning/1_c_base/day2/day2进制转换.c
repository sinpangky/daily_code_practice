#include <stdio.h>

// hw1:从键盘上输入字符，将小写字母转换成大写字母
void lower2uppercase() {
  char c;
  printf("Please input your character(from a to z): ");
  scanf("%c", &c);
  printf("The uppercase of %c is: %c\n", c, c - 32);  // upper = lower - 32
}

// hw2:进制转换
// 1)十进制转换为二进制
void decToBin(int n) {  // 递归求逆序
  if (n / 2 != 0) {
    decToBin(n / 2);
  }
  printf("%d", n % 2);
}
void dec2bin() {
  int dec;
  printf("Please input your d-number: ");
  scanf("%d", &dec);
  printf("The b-number of %d is: ", dec);
  decToBin(dec);  //调用递归
  printf("\n");
}
// 2)二进制转换为十进制
void bin2dec() {
  char a[100];
  printf("Please input your b-number: ");
  scanf("%s", a);
  int i = 0;
  int dec = 0;
  while (a[i] != '\0') {  // 原来的值*2+下一位 = 新的值
    dec = dec * 2 + (a[i] - '0');
    i++;
  }
  printf("The d-number of %s is: %d\n", a, dec);
}

// hw3:统计一个整数对应的二进制数的1的个数。输入一个整数（可正可负），
// 输出该整数的二进制包含1的个数。 
// 思考过程 
// 1111 1110 
// 1000 0010->-2 
// 0000 0010->2
// 2^(-2) = 1111 1100
// 正数：求1的个数
// 负数：1的个数 = （二进制长度 - 最低位1的位置） - （正数的1的个数-1）+1  **计算公式
// 最低位1的位置：mark = n^-n; 直到(mark>>position)%2 == 1

int AOOForPositive(int num) {  // 求正数中1的个数
  int count = 0;
  while (num != 0) {  // 直到除尽
    if (num % 2 == 1) {  
      count++;
    }
    num = num / 2;
  }
  return count;
}

void amountOfOne() {
  int num;
  printf("Please input your number: ");
  scanf("%d", &num);
  if (num == 0) {  // 输入为0
    printf("The amount of 1 is: 0\n");
  } else if (num > 0) {  // 输入为正
    printf("The amount of 1 is: %d\n", AOOForPositive(num));
  } else {  // 输入为负
    int mark = num ^ -num;  // 异或求最小1位置
    int i;
    for (i = 0; (mark >> i) % 2 == 0; i++);  // 最小1的位置
    printf("The amount of 1 is: %d\n",
           (int)sizeof(int)*8 - i - AOOForPositive(-num) + 2);  // 上面思考过程给出的计算公式
  }
}

int main() {
  // 作业1
  // lower2uppercase();
  // 作业2
  // dec2bin();
  bin2dec();
  // 作业3
  // amountOfOne();

  return 0;
}
