#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e6 + 5;
int MOD;
ll fact[N], inv[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = ifact[i - 1] * inv[i] % MOD;
}

ll C(int n, int k) {
  if (k<0 or k> n) return 0;
  return 1ll * fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n >> MOD;

  init();

  ll total = fact[3 * n];
  ll d0 = 1;
  ll d1 = (2ll * (fact[2 * n] - fact[n] + MOD) + fact[n] + MOD - 1) % MOD;

  ll not_d3 = 0;
  not_d3 += 2ll * C(2 * n, n) % MOD * fact[n] % MOD * fact[2 * n] % MOD;
  for (int i = 0; i <= n; i++) {
    ll sub = C(n, i) * C(n, n - i) % MOD * C(2 * n - i, n) % MOD * fact[n] % MOD * fact[n] % MOD * fact[n] % MOD;
    not_d3 = (not_d3 - sub + MOD) % MOD;
  }

  ll d2 = (not_d3 - d0 - d1 + 2ll * MOD) % MOD;
  ll d3 = (total - d0 - d1 - d2 + 3ll * MOD) % MOD;

  ll ans = (d0 * 0ll + d1 * 1ll + d2 * 2ll + d3 * 3ll) % MOD;
  cout << ans << "\n";

  return 0;
}

// n = 2
// [d]: {1, 45, 378, 296}