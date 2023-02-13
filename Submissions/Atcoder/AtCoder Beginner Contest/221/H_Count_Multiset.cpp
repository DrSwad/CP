#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; i++) {
    vector<int> ndp = dp;
    for (int j = i, mx = min(n, i * m); j <= mx; j += i) {
      for (int k = j; k <= n; k++) {
        ndp[k] += dp[k - j];
        if (ndp[k] >= MOD) ndp[k] -= MOD;
      }
    }
  }

  for (int i = 0) return 0;
}