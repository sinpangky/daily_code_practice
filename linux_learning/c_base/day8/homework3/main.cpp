#include <iostream>
using namespace std;
#define MAX 100

int sweet[MAX], temp[MAX];

int main() {
  int m;
  while (cin >> m, m) {
    int max = 0, min = 100, count = 0,tmax,tmin;
    for (int i = 0; i < m; i++) {
      cin >> sweet[i];
      max = (max <= sweet[i] ? sweet[i] : max);
      min = (min >= sweet[i] ? sweet[i] : min);
    }
    while (max != min) {
      for (int i = 0; i < m; i++) {
        temp[i] = sweet[i]/2;
      }
      for (int i = 1; i < m; i++) {
        sweet[i] = sweet[i]/2+temp[i-1];
        if(sweet[i]%2) sweet[i]+=1;
      }
      sweet[0] = sweet[0]/2+temp[m-1];
      if(sweet[0]%2) sweet[0]+=1;
      tmax = 0,tmin =100;
      for (int i = 0; i < m; i++) {
        tmax = (tmax <= sweet[i] ? sweet[i] : tmax);
        tmin = (tmin >= sweet[i] ? sweet[i] : tmin);
      }
      max = tmax;
      min = tmin;
      count++;
    }
    cout<<count<<" "<<max<<endl;
  }
}
