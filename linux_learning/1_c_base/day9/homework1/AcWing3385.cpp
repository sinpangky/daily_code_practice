#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
// #include <tuple>
using namespace std;

int n;

bool CheckString(const string &s) { return s.find("2012") != string::npos; }

int BFS(string s) {
  if (CheckString(s)) {
    return 0;
  }

  queue<pair<string, int>> visit_queue;  // 队列中同时保存字符串和步数
  set<string> visited;

  visit_queue.push(make_pair(s, 0));
  visited.insert(s);

  while (!visit_queue.empty()) {
    string current = visit_queue.front().first;
    int steps = visit_queue.front().second;
    visit_queue.pop();

    for (int i = 0; i < n - 1; i++) {
      string next = current;
      swap(next[i], next[i + 1]);

      if (visited.find(next) == visited.end()) {
        visited.insert(next);
        if (CheckString(next)) {
          return steps + 1;  // 找到解决方案，返回步数
        }
        visit_queue.push(make_pair(next, steps + 1));
      }
    }
  }
  return -1;  // 未找到解决方案
}

int main() {
  cin >> n;
  string s;
  cin >> s;

  int steps = BFS(s);
  cout << steps << endl;
  return 0;
}
