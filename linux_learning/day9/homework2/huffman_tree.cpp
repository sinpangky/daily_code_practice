#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> remain_node;

void InsertSorted(vector<int> &list, int value) {
  vector<int>::iterator it = lower_bound(list.begin(), list.end(), value);
  list.insert(it, value);
}

int main() {
  int n, value, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> value;
    InsertSorted(remain_node, value);
  }
  while (remain_node.size() != 1) {
    int s = remain_node[0] + remain_node[1];
    remain_node.erase(remain_node.begin());
    remain_node.erase(remain_node.begin());
    InsertSorted(remain_node, s);
    cnt += s;
  }
  cout << cnt << endl;
  return 0;
}