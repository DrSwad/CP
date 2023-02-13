#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
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

void test_case() {
  int n;
  cin >> n;

  vector<tuple<ll, ll, ll>> tree(n);
  for (auto & [x, y, p] : tree) cin >> x >> y >> p;

  ll ans = 0;
  for (int mask = 0; mask < 1 << n; mask++) {
    ll x1 = N, x2 = 0, y1 = N, y2 = 0;
    ll curr = 1;
    for (int i = 0; i < n; i++) {
      auto [x, y, p] = tree[i];
      if (mask >> i & 1) {
        x1 = min(x1, x);
        x2 = max(x2, x);
        y1 = min(y1, y);
        y2 = max(y2, y);
        (curr *= p) %= MOD;
      }
      else {
        (curr *= (100 - p)) %= MOD;
      }
    }
    ll area = max(0ll, (x2 - x1) * (y2 - y1));
    (curr *= area) %= MOD;
    (ans += curr) %= MOD;
  }

  cout << ans * binExp(binExp(100, -1), n) % MOD << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}