#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll n, ll p, ll r, ll b, ll k) {
  // cerr << n << " " << p << " " << r << " " << b << " " << k << endl;
  assert(1 <= k and k <= n);
  ll m = n / k;
  return k * p + n * r + m * (m - 1) / 2 * k * b + m * (n % k) * b;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, p, r, b;
  cin >> n >> p >> r >> b;

  ll ans = LLONG_MAX;
  ll m = 0;
  do {
    m = n / (n / (m + 1));
    ll R = n / m;
    ll L = n / (m + 1) + 1;
    ll k;
    if (2 * p - b * m - b * m * m <= 0) k = R;
    else k = L;
    ans = min(ans, solve(n, p, r, b, k) - p);
    // cerr << m << " " << k << " " << solve(n, p, r, b, n / m) << endl;
  } while (m != n);

  cout << ans << "\n";

  return 0;
}