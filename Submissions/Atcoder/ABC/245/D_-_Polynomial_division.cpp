#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  int k = n + m;

  vector<int> a(n + 1), c(k + 1);
  for (int &i : a) cin >> i;
  for (int &i : c) cin >> i;

  int zc;
  for (zc = 0; zc <= n and a[zc] == 0; zc++);
  a = vector<int>(a.begin() + zc, a.end());
  c = vector<int>(c.begin() + zc, c.end());
  n -= zc;
  k -= zc;

  vector<int> b(k + 1);
  for (int i = 0; i <= k; i++) {
    b[i] = c[i];
    for (int j = 1; j <= min(i, n); j++) {
      b[i] -= a[j] * b[i - j];
    }
    assert(b[i] % a[0] == 0);
    b[i] /= a[0];
  }

  for (int i = 0; i <= m; i++) {
    if (i) cout << " ";
    cout << b[i];
  }
  cout << "\n";

  return 0;
}