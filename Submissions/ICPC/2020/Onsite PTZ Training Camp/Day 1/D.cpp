#include <bits/stdc++.h>
using namespace std;

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

bool crt(long long k1,
  long long m1,
  long long k2,
  long long m2,
  long long &k,
  long long &m
  ) {
  k1 %= m1;
  if (k1 < 0) k1 += m1;
  k2 %= m2;
  if (k2 < 0) k2 += m2;
  long long x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  long long dx = m2 / g;
  long long delta = x / dx - (x % dx < 0);
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

long long in()
{
  long long n;
  scanf("%lld", &n);
  return n;
}
pair<long long, long long> ar[205];
long long dp[205][205], ar1[205], ar2[205];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  long long n = in();
  for (int i = 1; i <= n; i++)
  {
    ar[i].first = 0;
    ar[i].second = 0;
    ar1[i] = in();
  }
  for (int i = 1; i <= n; i++)
  {
    ar2[i] = in();
  }
  for (int i = 1; i <= n; i++)
  {
    int x = ar1[i], bla = 0;
    while (1)
    {
      if (bla == 0)
      {
        ar[i].first++;
        x = ar2[x];
        if (ar[i].first > 200)
        {
          puts("-1");
          exit(0);
        }
        if (x == i) bla = 1;
      }
      else if (bla == 1)
      {
        ar[i].second++;
        x = ar2[x];
        if (x == i)
        {
          if (ar[i].first == ar[i].second) ar[i].first = 0;
          break;
        }
      }
    }
  }

  long long k = 0, m = 1;
  __int128 mx = 1e18;
  for (int i = 1; i <= n; i++) {
    long long g = gcd(m, ar[i].second);
    if (__int128(m) * ar[i].second / g > mx) {
      puts("-1");
      exit(0);
    }
    if (!crt(ar[i].first, ar[i].second, k, m, k, m)) {
      puts("-1");
      exit(0);
    }
  }

  long long ans = k;
  printf("%lld\n", ans);

  return 0;
}