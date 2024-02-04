#include <algorithm>
#include <iostream>

using namespace std;

#define MMAX 101
#define NMAX 21
int cnt[NMAX][MMAX];
int a[NMAX];

int main() {
  int m, n;
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    cnt[0][i + 1] = 10000;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cnt[i][j] = cnt[i - 1][j];
      if (j >= a[i]) {
        cnt[i][j] = min(cnt[i - 1][j], cnt[i - 1][j - a[i]] + 1);
      }
    }
  }
  if (cnt[n][m] == 10000) {
    cout << 0;
  } else {
    cout << cnt[n][m];
  }
  return 0;
}