#include <stdio.h>
#include <string.h>

#define Size 5
typedef struct student {
  long number;
  char name[20];
  int class1;
  int class2;
  int class3;
} student;

void sort_by_number(student* stu) {
  int i, j;
  student key;
  for (i = 1; i < Size; i++) {
    key.number = stu[i].number;
    strcpy(key.name, stu[i].name);
    key.class1 = stu[i].class1;
    key.class2 = stu[i].class2;
    key.class3 = stu[i].class3;
    j = i - 1;
    while (j >= 0 && stu[j].number > key.number) {
      stu[j + 1].number = stu[j].number;
      strcpy(stu[j + 1].name, stu[j].name);
      stu[j + 1].class1 = stu[j].class1;
      stu[j + 1].class2 = stu[j].class2;
      stu[j + 1].class3 = stu[j].class3;
      j = j - 1;
    }
    stu[j + 1].number = key.number;
    strcpy(stu[j + 1].name, key.name);
    stu[j + 1].class1 = key.class1;
    stu[j + 1].class2 = key.class2;
    stu[j + 1].class3 = key.class3;
  }
}

void print_studnet(student* stu) {
  printf("学号         姓名            科一科二科三总分\n");
  for (int i = 0; i < Size; i++) {
    printf("%-12ld %-15s %-3d %-3d %-3d %-3d\n", stu[i].number, stu[i].name,
           stu[i].class1, stu[i].class2, stu[i].class3, stu[i].class1 + stu[i].class2 + stu[i].class3);
  }
}

void print_highest_score(student* stu) {
  printf("科一            科二            科三\n");
  int c1 = 0, c2 = 0, c3 = 0;
  for (int i = 0; i < Size; i++) {
    if (stu[i].class1 > stu[c1].class1) {
      c1 = i;
    }
    if (stu[i].class2 > stu[c2].class2) {
      c2 = i;
    }
    if (stu[i].class3 > stu[c3].class3) {
      c3 = i;
    }
  }
  printf("%-15s %-15s %-15s\n", stu[c1].name, stu[c2].name, stu[c3].name);
}

void print_average_score(student* stu) {
  printf("科一   科二   科三\n");
  int c1 = 0, c2 = 0, c3 = 0;
  for (int i = 0; i < Size; i++) {
    c1 += stu[i].class1;
    c2 += stu[i].class2;
    c3 += stu[i].class3;
  }
  printf("%-4.2f  %-4.2f  %-4.2f\n", (float)c1 / 5, (float)c2 / 5,
         (float)c3 / 5);
}

sort_by_all_score(student* stu) {
  int i, j;
  student key;
  for (i = 1; i < Size; i++) {
    key.number = stu[i].number;
    strcpy(key.name, stu[i].name);
    key.class1 = stu[i].class1;
    key.class2 = stu[i].class2;
    key.class3 = stu[i].class3;
    j = i - 1;
    while (j >= 0 && stu[j].class1 + stu[j].class2 + stu[j].class3 <
                         key.class1 + key.class2 + key.class3) {
      stu[j + 1].number = stu[j].number;
      strcpy(stu[j + 1].name, stu[j].name);
      stu[j + 1].class1 = stu[j].class1;
      stu[j + 1].class2 = stu[j].class2;
      stu[j + 1].class3 = stu[j].class3;
      j = j - 1;
    }
    stu[j + 1].number = key.number;
    strcpy(stu[j + 1].name, key.name);
    stu[j + 1].class1 = key.class1;
    stu[j + 1].class2 = key.class2;
    stu[j + 1].class3 = key.class3;
  }
  for (int k = 0; k < Size; k++)
  {
    printf("排名:%d %-15s\n",k+1,stu[k].name);
  }
}

int main() {
  student stu[Size];
  for (int i = 0; i < Size; i++) {
    scanf("%ld%s%d%d%d", &stu[i].number, &stu[i].name, &stu[i].class1,
          &stu[i].class2, &stu[i].class3);
  }
  // (1)
  sort_by_number(stu);
  print_studnet(stu);
  // (2)
  print_highest_score(stu);
  // (3)
  print_average_score(stu);
  // (4)
  sort_by_all_score(stu);
}

// // 测试用模版
// 12314 chengli 22 33 44
// 35245 chalgasdaf 44 11 66
// 21344 dsfadfas 66 22 11
// 98712 dafkjhk 55 99 11
// 83457 jkgses 33 66 77