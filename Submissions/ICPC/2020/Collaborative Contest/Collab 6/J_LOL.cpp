#include <bits/stdc++.h>
using namespace std;

const int n = 5;
const int m = 100;
const int MOD = 1e9 + 7;
int C[m + 1][m + 1];

int main() {
  for (int i = 0; i <= m; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }

  char s[n][m + 1];
  while (scanf("%s%s%s%s%s", s[0], s[1], s[2], s[3], s[4]) != EOF) {
    int nn = 2 * n;
    vector<vector<int>> dp(2, vector<int>(1 << nn, 0));
    dp[1][0] = 1;
    for (int i = 0; i < m; i++) {
      int dpi = i & 1;
      dp[dpi][0] = 1;
      for (int mask = 1; mask < 1 << nn; mask++) {
        dp[dpi][mask] = dp[dpi ^ 1][mask];
        for (int j = 0; j < nn; j++) {
          if (mask >> j & 1 and (j < n or s[j - n][i] == '1')) {
            (dp[dpi][mask] += dp[dpi ^ 1][mask ^ 1 << j]) %= MOD;
          }
        }
      }
    }

    long long ans = 1ll * dp[(m - 1) & 1][(1 << nn) - 1] * C[m - nn][n] % MOD * C[m - nn - n][n] % MOD;
    printf("%lld\n", ans);
  }

  return 0;
}