#include <bits/stdc++.h>
using namespace std;

const int N = 65;
const int MOD = 1e9 + 7;

int n;
int a[N];
long long dp[N][N][N];

int solve() {
  for (int i = 0; i <= n + 1; i++) {
    for (int l = 0; l <= n + 1; l++) {
      for (int r = 0; r <= n + 1; r++) {
        dp[i][l][r] = l > r;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int l = 1; l <= n; l++) {
      for (int r = l; r <= n; r++) {
        long long &cdp = dp[i][l][r];

        if (a[i] < l or r < a[i]) {
          cdp = dp[i - 1][l][r];
        } else {
          for (int p = l; p <= r; p++) {
            cdp += dp[i - 1][l][p - 1] * dp[i - 1][p + 1][r] * (p == a[i] ? 2 : 1);
            if (p % 8 == 0) cdp %= MOD; // since MOD * MOD * 8 < LLONG_MAX
          }
          cdp %= MOD;
        }
      }
    }
  }

  return dp[n][1][n];
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    printf("%d\n", solve());
  }

  return 0;
}