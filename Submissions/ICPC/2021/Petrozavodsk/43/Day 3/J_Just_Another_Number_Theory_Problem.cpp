#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> p(n);
  for (ll &i : p) cin >> i, i %= MOD;

  ll ans = 0;
  for (int len = 1; len <= p[0]; len++) {
    ll curr = 1;
    for (int i = 0; i < n; i++) {
      (curr *= ((p[i] + 1) - len + MOD) % MOD) %= MOD;
    }
    (ans += len == 1 ? curr : 2ll * curr) %= MOD;
  }

  cout << ans << "\n";

  return 0;
}