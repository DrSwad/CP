#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int R = 11;
const int N = 1005;
const int MOD = 1e9 + 7;

int t, cases;
ll f[R][N][N], ans[R][N][N], fac[N], comb[N][N], two[N];

int main() {
  two[0] = 1;
  for (int i = 1; i < N; ++i) two[i] = 2 * two[i - 1] % MOD;
  fac[0] = 1;
  for (int i = 1; i < N; ++i) fac[i] = i * fac[i - 1] % MOD;
  for (int i = 0; i < N; ++i) comb[i][0] = 1;
  for (int i = 1; i < N; ++i) for (int j = 1; j <= i; ++j) {
      comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
      if (comb[i][j] >= MOD) comb[i][j] -= MOD;
    }
  for (int r = 1; r < R; ++r) {
    f[r][0][0] = 1;
    for (int i = 1; i < N; ++i) {
      for (int j = 1; j <= i / r; ++j) {
        f[r][i][j] = (i - 1LL) * f[r][i - 1][j] % MOD;
        if (i >= r) f[r][i][j] = (f[r][i][j] + comb[i - 1][r - 1] * fac[r - 1] % MOD * f[r][i - r][j - 1]) % MOD;
      }
    }
  }
  for (int r = 1; r < R; ++r) {
    for (int i = 1; i < N; ++i) {
      for (int j = 1; j < N; ++j) {
        ans[r][i][j] = (ans[r][i][j - 1] + f[r][i][j] * (two[j] + MOD - 2)) % MOD;
      }
    }
  }
  cin >> t;
  while (t--) {
    int n, c, r;
    scanf("%d %d %d", &n, &c, &r);
    printf("Case %d: %lld\n", ++cases, ans[r][n][c]);
  }
  return 0;
}