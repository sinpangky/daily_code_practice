#include <stdio.h>

int amountOfPath(int m,int n) {
  int pathCount = 0;
  if(m>0 && n>0) {
    amountOfPath(m-1,n);
    amountOfPath(m,n-1);
  } else if(m>0) {
    amountOfPath(m-1,0);
  } else if(n>0) {
    amountOfPath(0,n-1);
  } else {
    count++;
  }
  return count;
}

int main() {
  int i,j;
  scanf("%d%d",&i,&j);
  printf("%d",amountOfPath(i,j));
  return 0;
}