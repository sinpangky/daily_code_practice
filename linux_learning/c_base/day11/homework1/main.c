#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  char id[10];
  char name[20];
  char gender[4];
  int score1;
  int score2;
  int score3;
} stu, *pstu;

int compare(const void *a, const void *b) {
  pstu aa = (pstu)a;
  pstu bb = (pstu)b;
  return bb->score1 + bb->score2 + bb->score3 - (aa->score1 + aa->score2 +
         aa->score3);
}

int main() {
  stu s[5];

  FILE *fp = fopen("data.txt", "r");
  if (NULL == fp) {
    perror("Unable to open the file");
    return -1;
  }
  for (int i = 0; i < 5; i++) {
    fscanf(fp, "%s %s %s %d %d %d\n", &s[i].id, &s[i].name, &s[i].gender,
           &s[i].score1, &s[i].score2, &s[i].score3);
  }
  fclose(fp);
  qsort(s, 5, sizeof(stu), compare);
  fp = fopen("data.txt", "w");
  for (int i = 0; i < 5; i++) {
    fprintf(fp, "%s %s %s %d %d %d\n", s[i].id,s[i].name,s[i].gender,s[i].score1,s[i].score2,s[i].score3);
  }
  fclose(fp);
  return 0;
}