#include <iostream>
#include <cstdio>
using namespace std;

int CountPrimeFactors(long n) {
  int count = 0;
  while (n % 2 == 0) {
    count++;
    n /= 2;
  }
  while (n % 3 == 0) {
    count++;
    n /= 3;
  }
  int i;
  for (i = 5; i <= n; i += 6) {
    while (n % i == 0) {
      count++;
      n /= i;
    }
    while (n % (i+2) == 0) {
      count++;
      n /= (i+2);
    }
  }
  return count;
}

int main() {
  long n;
  while (cin >> n) {
    printf("%d\n",CountPrimeFactors(n));
  }

  return 0;
}

// #include <bits/stdc++.h>
// using namespace std;
// bool add(long long n) {
//   if (n < 2) return false;
//   for (long long i = 2; i * i <= n; i++)
//     if (n % i == 0) return false;
//   return true;
// }
// int main() {
//   long long n;
//   while (cin >> n) {
//     int k = 0;
//     for (long long i = 2; i * i <= n; i++) {
//       if (add(i)) {
//         while (n % i == 0) n /= i, k++;
//       }
//     }
//     if (add(n)) k++;
//     cout << k << endl;
//   }
// }
