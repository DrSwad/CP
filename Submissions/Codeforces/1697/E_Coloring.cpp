#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_COMP = 4;
const int MOD = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }

  auto dist = [&](int i, int j) {
    return abs(x[i] - x[j]) + abs(y[i] - y[j]);
  };
  vector<vector<int>> order(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    iota(order[i].begin(), order[i].end(), 0);
    sort(
      order[i].begin(),
      order[i].end(),
      [&](int j, int k) {
      return dist(i, j) < dist(i, k);
    }
      );
  }

  auto verify = [&](vector<int> ids) {
    int sz = ids.size();
    if (sz == 1) return true;
    for (int i : ids) {
      for (int j : ids) {
        if (i == j) continue;
        if (dist(i, j) != dist(i, order[i][1])) return false;
      }
      if (n > sz and dist(i, order[i][1]) == dist(i, order[i][sz])) return false;
    }
    return true;
  };

  vector<bool> vis(n, false);
  vector<int> cnt(MAX_COMP, 0);

  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      for (int sz = MAX_COMP; sz >= 1; sz--) {
        if (sz <= n and verify(vector<int>(order[i].begin(), order[i].begin() + sz))) {
          cnt[sz - 1]++;
          for (int j = 0; j < sz; j++) {
            vis[order[i][j]] = true;
          }
          break;
        }
      }
    }
  }

  vector<ll> dp(n + 1, 0);
  dp[0] = 1;

  for (int sz = 1; sz <= MAX_COMP; sz++) {
    while (cnt[sz - 1]--) {
      vector<ll> ndp(n + 1, 0);

      for (int took = 0; took < n; took++) {
        (ndp[took + 1] += dp[took] * (n - took) % MOD) %= MOD;
      }

      if (sz > 1) {
        for (int took = 0; took <= n - sz; took++) {
          ll all_diff = 1;
          for (int i = 0; i < sz; i++) {
            (all_diff *= n - took - i) %= MOD;
          }

          (ndp[took + sz] += dp[took] * all_diff % MOD) %= MOD;
        }
      }

      swap(dp, ndp);
    }
  }

  ll ans = 0;
  for (int took = 0; took <= n; took++) {
    (ans += dp[took]) %= MOD;
  }

  cout << ans << "\n";

  return 0;
}