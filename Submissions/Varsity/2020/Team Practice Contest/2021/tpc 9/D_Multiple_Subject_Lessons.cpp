#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 20;
ll dp[N][N], ncr[35][35];

int main() {
  for (int i = 1; i < 32; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for (int j = 1; j < i; j++) {
      ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
    }
  }

  ll n, k;
  cin >> n >> k;

  for (int i = 0; i <= n; i++) dp[0][i] = 1;

  for (int i = 1; i <= n; i++) {
    for (int max_val = 1; max_val <= n; max_val++) {
      dp[i][max_val] = dp[i][max_val - 1];
      for (int len = 1; ; len++) {
        if (len * max_val > i) break;
        dp[i][max_val] += dp[i - max_val * len][max_val - 1] * ncr[len + k - 1][k - 1];
      }
      debug() << name(i) name(max_val) name(dp[i][max_val]);
    }
  }

  cout << dp[n][n] << '\n';

  return 0;
}