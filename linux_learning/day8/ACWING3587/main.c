#include <stdio.h>

#define N 1001

int father[N];
void Init(int n) {
  for (int i = 0; i < n; i++) {
    father[i] = i;
  }
}

int Find(int x) {
  int fx = father[x];
  if (fx == x) {
    return fx;
  } else {
    return Find(fx);
  }
}

void Union(int x, int y, int* cnt) {
  int fx = Find[x];
  int fy = Find[y];
  if (fx ! = fy) {
    --*cnt;
    father[fx] = fy;
  }
}

int main() {
  int m, n;
  int i, x, y;
  while (scanf("%d%d", &n, &m) != EOF) {
    Init(n);
    for (i = 0; i < m; i++) {
      scanf("%d%d", &x, &y);
      Union(x, y, &n);
    }
  }
}