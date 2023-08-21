#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll binExp(ll a, ll e, ll m) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

ll smallest_solution(ll a, ll r, ll m) {
  r %= m;
  if (r < 0) r += m;

  return r * binExp(a, -1, m) % m;
}

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  ll a, b, c, x;
  cin >> n >> a >> b >> c >> x;

  ll ans = 0;
  ll gbc = gcd(b, c);
  b /= gbc, c /= gbc;

  for (int i = 1; i <= n; i++) {
    ll rem = x - a * i;
    if (rem % gbc != 0) continue;
    rem /= gbc;
    if (rem<0 or rem> b * n + c * n) continue;

    // b * j + c * k = rem
    // => b * j = rem (mod c)
    ll j = smallest_solution(b, rem, c);
    ll dj = c;
    ll dk = b;
    ll k = (rem - b * j) / c;

    if (j == 0) {
      j += dj;
      k -= dk;
    }
    if (b * j > rem) continue;

    if (k > n) {
      ll mul = (k - n) / dk;
      k -= dk * mul;
      j += dj * mul;
      if (k > n) {
        k -= dk;
        j += dj;
      }
    }

    if (k <= 0) continue;
    if (j > n) continue;

    ll add = min((n - j) / dj + 1, (k - 1) / dk + 1);
    ans += add;
  }

  cout << ans << "\n";

  return 0;
}