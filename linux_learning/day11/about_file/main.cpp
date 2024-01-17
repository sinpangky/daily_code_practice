#include <stdio.h>
#include <string.h>

int main() {
  FILE* fp = fopen("file.txt","r");
  if (NULL == fp) {
    perror()
  }
}