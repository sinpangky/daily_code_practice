#include <stdio.h>

int main() {
  char c;
  int i;
  while ((c = getchar()) != EOF) {
    printf("%c", c);
  }
  while (scanf("%d", &i) != EOF) {
    printf("%d\n", i);
  }
  return 0;
}