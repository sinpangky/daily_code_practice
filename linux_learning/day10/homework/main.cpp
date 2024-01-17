#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  string s, substr;
  map<string, int> allsub;
  while (cin >> s) {
    allsub.clear();
    for (int i = 0; i < s.size(); ++i) {
      for (int len = 1; len + i <= s.size(); ++len) {
        substr = s.substr(i, len);
        allsub[substr]++;
      }
    }
    for (const auto& p : allsub) {
      if (p.second > 1) {
        cout << p.first << ' ' << p.second << '\n';
      }
    }
  }

  return 0;
}