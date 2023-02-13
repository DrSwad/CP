#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 2e5 + 5;
const int MX = 632;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<vector<int>> dp(2, vector<int>(n + 1));
  fill(dp[1].begin(), dp[1].end(), 0);
  dp[1][0] = 1;

  int dpi = 0;
  for (int kk = k + MX; kk >= k; kk--, dpi ^= 1) {
    fill(dp[dpi].begin(), dp[dpi].end(), 0);
    for (int x = 1; x <= n; x++) {
      if (x >= kk) {
        dp[dpi][x] = dp[dpi][x - kk] + dp[dpi ^ 1][x - kk];
        if (dp[dpi][x] >= MOD) dp[dpi][x] -= MOD;
      }
    }
    dp[dpi][0] = 1;
  }

  for (int x = 1; x <= n; x++) {
    if (x > 1) cout << " ";
    cout << dp[dpi ^ 1][x];
  }
  cout << "\n";

  return 0;
}