#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, t1, t2;
  cin >> n >> t1 >> t2;

  int tt1 = 0, tt2 = 0;
  int m = 0, t = 0;

  while (true) {
    if (tt1 == 0) {
      if (t > 0) m++;
    }
    if (tt2 == 0) {
      if (t > 0) m++;
    }
    if (tt1 <= 0 and tt2 <= 0 and m >= n) break;
    if (tt1 == 0 and m < n) tt1 += t1;
    if (tt2 == 0 and m < n) tt2 += t2;
    tt1--;
    tt2--;
    t++;
  }

  cout << m << " " << t << endl;

  return 0;
}