#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LCM_LIMIT = 550;

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
pair<long long, long long> inv_gcd(long long a, long long b) {
  a %= b;
  if (a < 0) a += b;
  if (a == 0) return {b, 0};

  long long s = b, t = a;
  long long m0 = 0, m1 = 1;

  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;

    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }

  if (m0 < 0) m0 += b / s;
  return {s, m0};
}

// @param m `1 <= m`
// @return x s.t. xa = r (mod m), 0 <= x < m/gcd(a, m)
long long smallest_solution(long long a, long long r, long long m) {
  r %= m;
  if (r < 0) r += m;

  auto [g, x] = inv_gcd(a, m);
  assert(r % g == 0);

  // return x * (r / g) % m; // use this if m <= INT_MAX
  return (long long)((__int128)x * (r / g) % m);
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return b[i] - a[i] < b[j] - a[j];
  }
    );

  ll a_sum = 0, b_sum = 0;
  for (int i : b) b_sum += i;

  vector<ll> val(n + 1);
  val[0] = b_sum;
  for (int i = 1; i <= n; i++) {
    int id = order[i - 1];
    a_sum += a[id];
    b_sum -= b[id];
    val[i] = a_sum + b_sum;
  }

  // debug(a, b, order, val);

  vector<vector<ll>> dp(LCM_LIMIT);
  for (int L = 1; L < LCM_LIMIT; L++) {
    for (int i = 0; i <= min(L - 1, n); i++) {
      ll curr = 0;
      for (int j = i; j <= n; j += L) {
        curr = max(curr, val[j]);
      }
      dp[L].push_back(curr);
    }
  }

  // debug(dp);

  int q;
  cin >> q;

  while (q--) {
    ll x, y;
    cin >> x >> y;

    ll g = __gcd(x, y);
    if (n % __gcd(x, y) != 0) {
      cout << "-1\n";
      continue;
    }
    ll cx = smallest_solution(x, n, y);
    if (x * cx > n) {
      cout << "-1\n";
      continue;
    }
    ll L = x * y / g;
    // debug(x, y, cx, cy, L);
    if (L < LCM_LIMIT) {
      cout << dp[L][x * cx] << "\n";
      continue;
    }

    ll ans = 0;
    for (ll j = x * cx; j <= n; j += L) {
      ans = max(ans, val[j]);
    }
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}