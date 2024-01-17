#include <stdio.h>
#include <string.h>

void big(char* arr[], int size, char** big1, char** big2) {
  if (strcmp(arr[0], arr[1]) >= 0) {
    *big1 = arr[0];
    *big2 = arr[1];
  } else {
    *big2 = arr[0];
    *big1 = arr[1];
  }
  for (int i = 2; i < size; i++) {
    if (strcmp(*big2, arr[i]) >= 0) {
      i++;
    } else {
      *big2 = arr[i];
      if (strcmp(*big1, *big2) < 0) {
        char* temp = *big1;
        *big1 = *big2;
        *big2 = temp;
      }
      i++;
    }
  }
}

int main() {
  char* p[5] = {"lele", "fenghua", "java", "python", "c"};
  char *big1, *big2;
  big(p, 5, &big1, &big2);
  puts(big1);
  puts(big2);
}