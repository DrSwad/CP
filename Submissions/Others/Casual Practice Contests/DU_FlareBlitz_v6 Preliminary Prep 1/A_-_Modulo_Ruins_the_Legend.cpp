#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<typename T>
T extgcd(T a, T b, T &x, T &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = extgcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}

template<typename T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }
  g = extgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + (T)((__int128)x * (c / g) % b);
  y = dy + (T)((__int128)y * (c / g) % a);
  g = abs(g);
  return true;
  // |x|, |y| <= max(|a|, |b|, |c|) [tested]
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<ll> v(n);
  for (ll &i : v) cin >> i;

  ll a = n % m;
  ll b = (n * (n + 1) / 2) % m;

  ll sum = 0;
  for (ll &i : v) sum += i;
  sum %= m;

  ll gab = gcd(a, b);
  ll g = gcd(m, gab);
  ll ans = sum % g;

  cout << ans << "\n";
  ll c;
  {
    ll _0 = (ans - sum + m) % m, _1, _2;
    ll gc;
    assert(diophantine(gab, m, _0, gc, _1, _2));
    c = gc * gab;
  }
  ll s, k;
  assert(diophantine(a, b, c, s, k, g));
  s = (s % m + m) % m;
  k = (k % m + m) % m;
  cout << s << " " << k << "\n";

  return 0;
}