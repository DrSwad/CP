#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 15;
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

int n;
int a[N];
ll pair_prod[1 << N], inv_pair_prod[1 << N];
ll scc_prob[1 << N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  if (n == 1) {
    puts("1");
    return 0;
  }

  for (int mask = 0; mask < 1 << n; mask++) {
    if (__builtin_popcount(mask) < 2) pair_prod[mask] = 1;
    else {
      int fix_lsb = __builtin_ctz(mask);

      ll curr_prod = 1;
      {
        int nmask = mask - (1 << fix_lsb);
        while (nmask) {
          int lsb = __builtin_ctz(nmask);
          (curr_prod *= (a[fix_lsb] + a[lsb])) %= MOD;
          nmask &= nmask - 1;
        }
      }

      int nmask = mask - (1 << fix_lsb);
      pair_prod[mask] = (ll)pair_prod[nmask] * curr_prod % MOD;
    }
    inv_pair_prod[mask] = binExp(pair_prod[mask], -1);
  }

  ll ans = 0;

  for (int mask = 1; mask < 1 << n; mask++) {
    int tot_bits = __builtin_popcount(mask);
    scc_prob[mask] = 1;

    for (int submask = (mask - 1) & mask; submask > 0; submask = (submask - 1) & mask) {
      ll submask_prod = 1;
      {
        int _submask = submask;
        while (_submask) {
          int lsb = __builtin_ctz(_submask);
          (submask_prod *= a[lsb]) %= MOD;
          _submask &= _submask - 1;
        }
      }

      ll curr_prob = scc_prob[submask];
      int xor_bits = __builtin_popcount(mask ^ submask);
      while (xor_bits--) (curr_prob *= submask_prod) %= MOD;

      (curr_prob *= inv_pair_prod[mask]) %= MOD;
      (curr_prob *= pair_prod[submask]) %= MOD;
      (curr_prob *= pair_prod[mask ^ submask]) %= MOD;

      (scc_prob[mask] += MOD - curr_prob) %= MOD;

      if (tot_bits == n) {
        (ans += curr_prob * __builtin_popcount(submask)) %= MOD;
      }
    }

    if (tot_bits == n) {
      (ans += scc_prob[mask] * n) %= MOD;
    }
  }

  cout << ans << "\n";

  return 0;
}