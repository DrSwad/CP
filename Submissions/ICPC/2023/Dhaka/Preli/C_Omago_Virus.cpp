#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 998244353;
const int N = 405;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int C[N][N];
int Ci[N][N];

void init() {
  for (int n = 0; n < N; n++) {
    for (int k = 0; k <= n; k++) {
      if (k == 0 or k == n) C[n][k] = 1;
      else C[n][k] = (C[n - 1][k] + C[n - 1][k - 1]) % mod;
      Ci[n][k] = binExp(C[n][k], -1);
    }
  }
}

void test_case() {
  int n, k, m;
  cin >> n >> k >> m;

  vector<vector<int>> p(n + 1, vector<int>(n + 1));
  for (int m = 1; m <= n; m++) {
    p[m][0] = 1;
    int frac = (ll)C[m - 1][k] * Ci[n - 1][k] % mod;
    for (int i = 0; i < m; i++) {
      p[m][0] = (ll)p[m][0] * frac % mod;
    }

    for (int x = 1; x <= n - m; x++) {
      p[m][x] = 1;
      int frac = (ll)C[m - 1 + x][k] * Ci[n - 1][k] % mod;
      for (int i = 0; i < m; i++) {
        p[m][x] = (ll)p[m][x] * frac % mod;
      }

      for (int y = 0; y < x; y++) {
        p[m][x] = (p[m][x] - (ll)p[m][y] * C[x][y] % mod + mod) % mod;
      }
    }
  }

  vector<int> dp(n + 1);
  dp[n] = 0;

  for (int m = n - 1; m >= 1; m--) {
    int up = p[m][0];
    for (int x = 1; x <= n - m; x++) {
      up = (up + (ll)p[m][x] * (1 + dp[m + x]) % mod * C[n - m][x] % mod) % mod;
    }
    dp[m] = (ll)up * binExp((1 + mod - p[m][0]) % mod, -1) % mod;
  }

  cout << dp[m] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}