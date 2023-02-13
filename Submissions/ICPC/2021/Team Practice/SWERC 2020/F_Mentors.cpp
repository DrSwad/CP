#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, n, m;
  cin >> r >> n >> m;

  if (n == 1) {
    cout << (1 % m) << "\n";
    return 0;
  }

  if (r == n) {
    cout << "0\n";
    return 0;
  }

  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
  dp[1][0] = 1;

  for (int i = 2; i <= n; i++) {
    for (int cnt2 = 0; cnt2 < i; cnt2++) {
      int cnt0 = cnt2 + 1;
      int cnt1 = i - cnt0 - cnt2;
      if (cnt1 < 0) continue;

      // add to cnt0
      (dp[i][cnt2] += dp[i - 1][cnt2] * cnt0 % m) %= m;
      // add to cnt1
      if (cnt1 > 0) (dp[i][cnt2 + 1] += dp[i - 1][cnt2] * (cnt1 - 1) % m) %= m;
    }
  }

  int fixed = n - r;
  int flex = r - 1;

  vector<vector<ll>> dp2(flex + 1, vector<ll>(n, 0));
  fill(dp2[flex].begin(), dp2[flex].end(), 1);

  for (int i = flex - 1; i >= 0; i--) {
    int tot = (fixed + 1) + i;
    for (int cnt2 = 0; cnt2 < tot; cnt2++) {
      int cnt0 = cnt2 + 1;
      int cnt1 = tot - cnt0 - cnt2;
      if (cnt1 < 0) continue;
      // add to cnt0
      (dp2[i][cnt2] += dp2[i + 1][cnt2] * (cnt0 - 1) % m) %= m;
      // add to cnt1
      (dp2[i][cnt2] += dp2[i + 1][cnt2 + 1] * cnt1 % m) %= m;
    }
  }

  ll ans = 0;
  for (int cnt2 = 0; cnt2 <= fixed; cnt2++) {
    int cnt0 = cnt2 + 1;
    int cnt1 = fixed - cnt0 - cnt2;
    if (cnt1 < 0) continue;
    // add to cnt0
    (ans += dp[fixed][cnt2] * dp2[0][cnt2] % m * cnt0 % m) %= m;
    // add to cnt1
    (ans += dp[fixed][cnt2] * dp2[0][cnt2 + 1] % m * cnt1 % m) %= m;
  }

  cout << ans << "\n";

  return 0;
}