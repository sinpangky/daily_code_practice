#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

const int N = 1010;
int n, m, a[N][N], r[N][4], c[N][4];  // r[N][0]是第n行的值，r[N][1]是对应值位置
queue<int> q;

// 给坐标[i, j]赋值为x
// 同时判断第i 行是否有两个点，第j 列是否有两个点
void add(int i, int j, int x) {
  a[i][j] = x;
  // 如果第i 行一个点都没有，给定第一个点的值到r[i][0],列数为r[i][1]
  // 其次如果第i
  // 行没第二个点，给定第二个点的值到r[i][2],列数为r[i][3]，并且加入到bfs中
  // 如果还有第三个点其实就不进行操作
  if (!r[i][0])
    r[i][0] = x, r[i][1] = j;
  else if (!r[i][2])
    r[i][2] = x, r[i][3] = j, q.push(i * 2 + 1);  // 如果是行扩展，加入奇数
  // 对列进行同等操作
  if (!c[j][0])
    c[j][0] = x, c[j][1] = i;
  else if (!c[j][2])
    c[j][2] = x, c[j][3] = i, q.push(j * 2);  // 如果是列扩展，加入偶数
}

// typedef pair<int, int> IntPair;
typedef vector<pii> IntPairVector;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      int x;
      scanf("%d", &x);
      if (x) add(i, j, x);  // 给[i, j] 赋值 x
    }

  vector<pii> ans;  // frist 里面存[x, y]坐标，sceond里面存值
  while (q.size()) {
    int now = q.front() / 2, f = q.front() % 2;
    q.pop();  // 取出行号或者列号
    if (f) {  // 如果是行扩展
      int suf =
          (r[now][2] - r[now][0]) / (r[now][3] - r[now][1]);  // 得到等差值
      int start = r[now][0] - (r[now][1] * suf);  // 求得第一个点的值
      for (int i = 0; i < m; i++) {
        if (!a[now][i]) {  // 如果a[now][i]是0，将a[now][i]按照等差公式赋值
          add(now, i, start + i * suf);  // 赋值
          ans.push_back(
              {now * 2000 + i, start + i * suf});  // 加入[坐标，值]答案数组中
        }
      }
    } else {  // 列扩展，以下同理
      int suf = (c[now][2] - c[now][0]) / (c[now][3] - c[now][1]);
      int start = c[now][0] - (c[now][1] * suf);
      for (int i = 0; i < n; i++) {
        if (!a[i][now]) {
          add(i, now, start + i * suf);
          ans.push_back({i * 2000 + now, start + i * suf});
        }
      }
    }
  }
  sort(ans.begin(), ans.end());  // 按照坐标排序

  // 通过迭代器遍历容器并输出内容
  for (IntPairVector::iterator it = ans.begin(); it != ans.end(); ++it) {
    pii currentPair = *it;
    int xy = currentPair.first;
    int val = currentPair.second;
    printf("%d %d %d\n", xy / 2000 + 1, xy % 2000 + 1, val);
  }

  // 看完点赞！！！
  return 0;
}