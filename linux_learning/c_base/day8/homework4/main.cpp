#include <iostream>
#include <string>
using namespace std;

void BubbleSort(string &s) {
  int n = s.length();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (s[j] > s[j + 1]) {
        swap(s[j], s[j + 1]);
      }
    }
  }
}

void permute(string &s,int l,int r) {
  if(l == r){
    cout<<s<<'\n';
  } else {
    for(int i =l;i <=r;i++){
      // if(s[l]!= s[i] || l ==i) 
      {
        swap(s[l],s[i]);
        permute(s,l+1,r);
        swap(s[l],s[i]);
      }
    }
  }
}

int main() {
  string s;
  cin >> s;
  BubbleSort(s);
  permute(s,0,s.length()-1);
  // do{
  //   cout<< s << endl;
  // }while(next_permutation(s.begin(),s.end()));

  return 0;
}


// #include <iostream>
// #include <string>
// using namespace std;

// void BubbleSort(string &s) {
//     int n = s.length();
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (s[j] > s[j + 1]) {
//                 swap(s[j], s[j + 1]);
//             }
//         }
//     }
// }

// void permute(string &s, int l, int r) {
//     if (l == r) {
//         cout << s << endl;
//     } else {
//         for (int i = l; i <= r; i++) {
//             swap(s[l], s[i]);
//             permute(s, l + 1, r);
//             swap(s[l], s[i]); // backtrack
//         }
//     }
// }

// int main() {
//     string s;
//     cin >> s;
//     BubbleSort(s);
//     permute(s, 0, s.length() - 1);
//     return 0;
// }
