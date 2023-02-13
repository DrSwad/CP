#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 11;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int n, m, k;
ll dp[N][N][N + N];
int dm[] = {-1, -2, 0, 0};
int dk[] = {0, 0, -1, -2};

int main() {
  cin >> n >> m >> k;

  dp[0][0][0] = 1;
  for (int sum = 1; sum <= m + k; sum++) {
    for (int cm = 0; cm <= m; cm++) {
      int ck = sum - cm;
      if (ck < 0 or ck > k) continue;

      for (int i = 0; i < 4; i++) {
        int nm = cm + dm[i];
        int nk = ck + dk[i];
        if (nm < 0 or nk < 0) continue;

        for (int tot = 0; tot < m + k; tot++) {
          (dp[cm][ck][tot + 1] += dp[nm][nk][tot]) %= MOD;
        }
      }
    }
  }

  ll ans = 0;
  for (int tot = 0; tot <= min(n, m + k); tot++) {
    int up = n - tot + tot + 1 - 1;
    int down = tot + 1 - 1;
    ll curr = dp[m][k][tot];
    for (int i = 0; i < down; i++) {
      (curr *= up - i) %= MOD;
      (curr *= binExp(i + 1, -1)) %= MOD;
    }
    (ans += curr) %= MOD;
  }

  cout << ans << endl;

  return 0;
}