#include <bits/stdc++.h>
using namespace std;

const int N = 50 + 5;
const int M = 1e5 + 5;
const int MOD = 998244353;

int n, m;
int l[N], r[N];
int sp[M], mu[M];

void sieve() {
  for (int p = 2; p < M; p++) {
    for (int q = p; q < M; q += p) {
      if (sp[q] == 0) {
        sp[q] = p;
      }
    }
  }
}

void calcMu() {
  mu[1] = 1;

  for (int i = 2; i < M; i++) {
    int p = sp[i];
    int pp = 1;

    int ii = i;
    int e = 0;
    while (ii % p == 0) {
      ii /= p;
      pp *= p;
      e++;
    }

    mu[i] = ii > 1 ? mu[pp] * mu[ii] : e == 1 ? -1 : 0;
  }
}

int calc(int d) {
  int mm = m / d;
  for (int i = 1; i <= n; i++) {
    mm -= (l[i] - 1) / d;
  }
  if (mm <= 0) return 0;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    a[i] = r[i] / d - (l[i] - 1) / d;
  }

  vector<int> dp(mm + 1, 1);

  for (int i = 1; i <= n; i++) {
    for (int s = mm; s > 0; s--) {
      int en = s - 1;
      int st = s - a[i] - 1;
      dp[s] = dp[en] - (st >= 0 ? dp[st] : 0);
      if (dp[s] < 0) dp[s] += MOD;
    }
    dp[0] = 0;
    for (int s = 1; s <= mm; s++) {
      dp[s] += dp[s - 1];
      if (dp[s] >= MOD) dp[s] -= MOD;
    }
  }

  return dp[mm];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
  }

  sieve();
  calcMu();

  int ans = 0;
  for (int d = 1; d <= m; d++) {
    int curr = calc(d);
    ans += mu[d] * curr;
    if (ans < 0) ans += MOD;
    if (ans >= MOD) ans -= MOD;
  }

  cout << ans << endl;

  return 0;
}