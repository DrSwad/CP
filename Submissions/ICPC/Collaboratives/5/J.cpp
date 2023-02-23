#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 2e3 + 5;

int n;
int f[N];
int nCk[N][N];

void update(int p, int v) {
  while (p <= n) {
    (f[p] += v) %= MOD, p += p & -p;
  }
}
int pref(int p) {
  int ret = 0;
  while (p) {
    (ret += f[p]) %= MOD, p -= p & -p;
  }
  return ret;
}

void init() {
  for (int n = 0; n < N; n++) {
    nCk[n][0] = nCk[n][n] = 1;
    for (int k = 1; k < n; k++) {
      nCk[n][k] = (nCk[n - 1][k] + nCk[n - 1][k - 1]) % MOD;
    }
  }
}

int main() {
  init();

  scanf("%d", &n);

  vector<int> p(n + 1), q(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    q[p[i]] = i;
  }

  vector<vector<int>> dp(n + 1, vector<int>(n + 1));
  fill(dp[1].begin(), dp[1].end(), 1);

  for (int len = 2; len <= n; len++) {
    memset(f, 0, sizeof f);
    for (int i = n; i >= 1; i--) {
      dp[len][i] = (pref(n) - pref(q[i]) + MOD) % MOD;
      update(q[i], dp[len - 1][i]);
    }
  }

  vector<int> dp2(n + 1);
  dp2[1] = 1;
  for (int i = 2; i <= n; i++) {
    int in = 1;
    for (int j = 1; j <= n; j++) {
      in = 1ll * in * i % MOD;
    }
    dp2[i] = in;

    for (int j = i - 1, k = -1; j >= 1; j--) {
      (dp2[i] += k * dp2[j] * 1ll * nCk[i][j] % MOD + MOD) %= MOD;
    }
  }

  int ans = 0;
  for (int len = 1; len <= n; len++) {
    for (int i = 1; i <= n; i++) {
      (ans += dp[len][i] * 1ll * dp2[len] % MOD) %= MOD;
    }
  }

  cout << ans << endl;

  return 0;
}