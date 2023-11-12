#include <bits/stdc++.h>
using namespace std;
const long long INF = 1000000000000000000;
int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int j = 0; j < n; j++) {
      cin >> a[j];
    }
    long long P = 1;
    bool big = false;
    for (int j = 0; j < n; j++) {
      if (P >= (INF + a[j] - 1) / a[j]) {
        big = true;
        break;
      } else {
        P *= a[j];
      }
    }
    vector<int> p;
    for (int j = 0; j < n; j++) {
      if (a[j] != 1) {
        p.push_back(j);
      }
    }
    int cnt = p.size();
    if (big) {
      cout << p[0] + 1 << ' ' << p[cnt - 1] + 1 << endl;
    } else if (cnt == 0) {
      cout << 1 << ' ' << 1 << endl;
    } else {
      long long mx = -1;
      int l = 0, r = 0;
      for (int j = 0; j < cnt; j++) {
        long long cp = a[p[j]], cs = a[p[j]];
        for (int k = j; k < cnt; k++) {
          if (k > j) {
            cp *= a[p[k]];
            cs += p[k] - p[k - 1] - 1;
            cs += a[p[k]];
          }
          if (cp - cs >= mx) {
            mx = cp - cs;
            l = p[j];
            r = p[k];
          }
        }
      }
      cout << l + 1 << ' ' << r + 1 << endl;
    }
  }
}