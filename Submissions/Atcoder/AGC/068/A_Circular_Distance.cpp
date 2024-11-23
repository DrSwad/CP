#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int L = 1e6 + 5;
const ll MOD = 998244353;

ll l, n;
ll fact[L], inv[L], inv_fact[L];

void init() {
  fact[0] = 1ll;
  for (int i = 1; i < L; i++) {
    fact[i] = fact[i - 1] * i % MOD;
  }
  inv[1] = 1ll;
  for (int i = 2; i < L; i++) {
    inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
  }
  inv_fact[0] = 1ll;
  for (int i = 1; i < L; i++) {
    inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
  }
}

ll C(ll n, ll k) {
  if (k < 0 or n < k) return 0;
  return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

ll ways_to_sum(ll sum, ll vars) {
  return C(sum + vars - 1, vars - 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  cin >> l >> n;

  ll ans = 0;

  for (ll d = 1; d <= l / 2; d++) {
    ll w = l - 2 * d;
    ll sum = C(l - 1, n - 1);
    for (ll alt = 0; alt <= l / (w + 2); alt++) {
      ll k = 2 * alt + 2;
      ll ways_to_partition_n = ways_to_sum(n + 1 - k, k);
      ll ways_to_place = ways_to_sum(d - n - alt * w, n);
      sum = (sum + MOD - ways_to_partition_n * ways_to_place % MOD) % MOD;
    }
    ans = (ans + sum) % MOD;
  }

  ans = ans * l % MOD * inv[n] % MOD;

  cout << ans << "\n";

  return 0;
}