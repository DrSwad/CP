#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll remaining;
  cin >> remaining;

  int logn = 32 - __builtin_clz(n);
  vector<vector<int>> sp(n, vector<int>(logn, -1));

  for (int i = 0; i < n; i++) {
    sp[i][0] = i;
  }
  for (int j = 1; j < logn; j++) {
    for (int i = 0; i < n; i++) {
      if (i + (1 << j) <= n) {
        int l = sp[i][j - 1];
        int r = sp[i + (1 << (j - 1))][j - 1];
        sp[i][j] = a[l] >= a[r] ? l : r;
      }
    }
  }

  auto query = [&](int l, int r) {
    int len = r - l + 1;
    int j = 31 - __builtin_clz(len);
    int L = sp[l][j];
    int R = sp[r - (1 << j) + 1][j];
    return a[L] >= a[R] ? L : R;
  };

  ll ans = 0;
  vector<vector<tuple<int, int, int>>> to_process(n + 1);
  to_process[n].emplace_back(n, 0, n - 1);

  for (int len = n; len >= 1; len--) {
    for (auto [h, l, r] : to_process[len]) {
      int mx_i = query(l, r);
      int mx_take = h - a[mx_i];
      int take = min((ll)mx_take, remaining / len);

      ans += 1ll * take * (len - 1);
      remaining -= 1ll * take * len;

      if (take < mx_take and remaining > 0) {
        ans += remaining - 1;
        remaining = 0;
      }

      if (l < mx_i) to_process[mx_i - l].emplace_back(a[mx_i], l, mx_i - 1);
      if (mx_i < r) to_process[r - mx_i].emplace_back(a[mx_i], mx_i + 1, r);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}