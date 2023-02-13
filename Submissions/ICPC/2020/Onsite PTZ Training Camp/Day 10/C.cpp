#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
  int n;
  vector<int> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, 0);
  }
  void update(int p, int v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  int pref(int p) {
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  int range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> bigger(2, vector<int>(n));
  int mx = *max_element(a.begin(), a.end());
  for (int it = 0; it < 2; it++) {
    BIT bit(mx);
    for (int i = 0; i < n; i++) {
      bigger[it][i] = bit.range(a[i] + 1, mx);
      bit.update(a[i], 1);
    }

    reverse(a.begin(), a.end());
  }
  reverse(bigger[1].begin(), bigger[1].end());

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += min(bigger[0][i], bigger[1][i]);
  }

  cout << ans << "\n";

  return 0;
}