#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  int n;
  cin >> n;

  vector<ll> a(n);
  vector<ll> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; i++) {
    cout << "1 " << 1 << " " << i << endl;

    int k;
    ll res;
    cin >> k >> res;

    if (k == i) a[i - 1] = res * binExp(dp[i - 1], -1) % MOD;
    else {
      a[i - 1] =
          ((res - dp[k] + MOD) % MOD) * binExp(dp[k - 1], -1) % MOD;
    }

    for (int j = i; j > 0; j--) {
      (dp[j] += dp[j - 1] * a[i - 1] % MOD) %= MOD;
    }
  }

  cout << 2;
  for (int i = 0; i < n; i++) { cout << " " << a[i]; }
  cout << endl;

  return 0;
}