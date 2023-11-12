#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  n = 1 << 20;
  vector<int> freq(n, 0);
  for (int i : a) freq[i]++;

  int logn = 21;

  vector sub(logn, vector(n, 0));
  vector sup(logn, vector(n, 0));
  sub[0] = freq;
  sup[0] = freq;

  for (int i = 1; i < logn; i++) {
    for (int mask = 0; mask < n; mask++) {
      if (mask >> (i - 1) & 1) {
        sub[i][mask] = sub[i - 1][mask] + sub[i - 1][mask - (1 << (i - 1))];
        sup[i][mask] = sup[i - 1][mask];
      }
      else {
        sub[i][mask] = sub[i - 1][mask];
        sup[i][mask] = sup[i - 1][mask] + sup[i - 1][mask + (1 << (i - 1))];
      }
    }
  }

  for (int i : a) {
    int ii = (n - 1) ^ i;
    int sz = a.size();
    cout << sub[logn - 1][i] << " " << sup[logn - 1][i] << " " << sz - sub[logn - 1][ii] << "\n";
  }

  return 0;
}