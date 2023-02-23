#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3005;
const int mod = (int)998244353;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

ll fact[2 * N], ifact[2 * N], inv[2 * N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < 2 * N; i++) inv[i] = (ll)inv[mod % i] * (mod - mod / i) % mod;
  for (int i = 1; i < 2 * N; i++) fact[i] = (ll)fact[i - 1] * i % mod;
  for (int i = 1; i < 2 * N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % mod;
}

ll C(int n, int k) {
  if (k<0 or k> n) return 0;
  return fact[n] * ifact[k] % mod * ifact[n - k] % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n, m;
  cin >> n >> m;

  vector<ll> dp(n + 1, 0ll);
  dp[0] = 1ll;

  vector<ll> mCl(n, 0ll);
  mCl[0] = 1ll;
  {
    for (int l = 1; l < n and l <= m - 2; l++) {
      mCl[l] = mCl[l - 1];
      mCl[l] = mCl[l] * ((m - 2) - (l - 1)) % mod;
      mCl[l] = mCl[l] * binExp(l, -1) % mod;
    }
  }

  for (int len = 1; len <= n; len++) {
    for (int l = 0; l < len; l++) {
      int r = (len - 1) - l;
      (dp[len] += C(l + r, r) * fact[l] % mod * dp[r] % mod * mCl[l] % mod * (l == 0 ? 2ll : 1ll) % mod) %= mod;
    }
  }

  cout << dp[n] << "\n";

  return 0;
}