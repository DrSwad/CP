#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 1e5;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    (ans += (ll)i * (n - i)) %= MOD;
  }
  (ans *= binExp((ll)n * n % MOD, -1)) %= MOD;
  cout << ans << "\n";

  return 0;
}