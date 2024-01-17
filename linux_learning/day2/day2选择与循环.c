#include <stdio.h>
#define MAXNUM1 101
#define MAXNUM2 102

// hw1

// hw1.1
void findTheSingle() {
  int integ[MAXNUM1];
  printf("Please input 101 integers with 50 integers appealing twice:\n");
  for (int i = 0; i < MAXNUM1; i++) {  // 读入 MAXNUM1 个整数
    scanf("%d", &integ[i]);
  }
  int single = integ[0];
  for (int i = 1; i < MAXNUM1; i++) {
    single =
        single ^
        integ
            [i];  // 利用异或运算的结合律和交换律，最终得到的single就是唯一的不同的数
  }
  printf("The single integer is: %d\n", single);
}

// hw1.2
void findTheTwoSingle() {
  int integ[MAXNUM2];
  int pre, pos;
  int num1, num2;
  // 前面和findTheSingle()相同，找出不同的两个数的异或值
  printf("Please input 102 integers with 50 integers appealing twice:\n");
  for (int i = 0; i < MAXNUM2; i++) {
    scanf("%d", &integ[i]);
  }
  pre = integ[0];
  for (int i = 1; i < MAXNUM2; i++) {
    pre = pre ^ integ[i];  // 得到不同的两个数的异或值
  }
  // 开始分类
  pre = pre ^ -pre;
  for (pos = 1; (pre >> pos) % 2 == 1; pos++)
    ;
  // 找到异或值中为1的位置，并用这个位置将数组中的元素分为两批
  pre = 1 << (pos - 1);
  num1 = 0;
  num2 = 0;
  for (int i = 0; i < MAXNUM2; i++) {
    if (integ[i] ^ pre) {
      num1 = num1 ^ integ[i];
    } else {
      num2 = num2 ^ integ[i];
    }
  }
  printf("The two single integers are: %d and %d\n", num1, num2);
}

// hw2

// hw2.1
int dayOfYear(int year, int month, int day) {
  int dayOfMon[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((year) % 4 == 0) {
    dayOfMon[1] = 29;
  } else {
    dayOfMon[1] = 28;
  }
  for (int i = 0; i < month - 1; i++) {
    day += dayOfMon[i];
  }
  return day;
}

// hw2.2
int gapDayOf2Date(int year, int month, int day, int year1, int month1,
                  int day1) {
  return 365*(year1 - year)+(year1- year)/4+dayOfYear(year1,month1,day1)-dayOfYear(year,month,day);
}

// hw2.3
int weekOfDate(int year, int month, int day){
  return (gapDayOf2Date(1995,1,1,year,month,day)-1)%7;
}

// hw2.4
void dateOfTomorrow(int *year, int* month,int* day){
  int feb;
  if((*year)%4 == 0) {
    feb = 29;
  } else {
    feb =28;
  }
  if(*day == 31 && *month ==12) {
    (*year)++;
    *month =1;
    *day =1;
  } else if(*day ==31 || *day ==30) {
    (*month)++;
    *day =1;
  } else if (*day == feb && *month == 2){
    *month =3;
    *day =1;
  } else {
    (*day)++;
  }
}

int main() {
  // // hw1
  
  // // hw1.1
  // findTheSingle();
  
  // // hw1.2
  // findTheTwoSingle();
  // putchar('\n');

  // // hw2

  // // hw2.1
  int year, month, day;
  // printf("Please input the date in format 'YYYY MM DD': ");
  // scanf("%d%d%d", &year, &month, &day);
  // printf("The day of the year is %d\n", dayOfYear(year, month, day));
  
  // // hw2.2
  // int year1, month1, day1;
  // printf("Please input 2 date in format 'YYYY MM DD YYYY MM DD'(with the earlier date in front): ");
  // scanf("%d%d%d%d%d%d", &year, &month, &day, &year1, &month1, &day1);
  // printf("Gap day of the 2 date is: %d\n",
  //        gapDayOf2Date(year, month, day, year1, month1, day1));
  
  // hw2.3
  // char *a;
  // printf("Please input the date in format 'YYYY MM DD'(better after A.D.1995): ");
  // scanf("%d%d%d", &year, &month, &day);
  // switch (weekOfDate(year, month, day))
  // {
  // case 1:
  //   a = "Monday";
  //   break;
  // case 2:
  //   a = "Tuesday";
  //   break;
  // case 3:
  //   a = "Wednsday";
  //   break;
  // case 4:
  //   a = "Thursday";
  //   break;
  // case 5:
  //   a = "Friday";
  //   break;
  // case 6:
  //   a = "Saturday";
  //   break;
  // case 0:
  //   a = "Sunday";
  //   break;
  // default:
  //   a = "ERROR";
  //   break;
  // }
  // printf("The week of the date is %s\n", a);

  char a[][10] = {"Monday","Tuesday","Wednsday","Thursday","Friday","Saturday","Sunday"};
  printf("Please input the date in format 'YYYY MM DD'(better after A.D.1995): ");
  scanf("%d%d%d", &year, &month, &day);
  printf("The week of the date is %s\n", a[weekOfDate(year, month, day)]);
  
  // // hw2.4
  // int num;
  // printf("Please input the date and the number of days in format 'YYYY MM DD num': ");
  // scanf("%d%d%d%d", &year, &month, &day,&num);
  // for(;num>0;num--){
  //   dateOfTomorrow(&year,&month,&day);
  // }
  // printf("The date after that days is %4d %-2d %-2d\n", year, month, day);

  return 0;
}