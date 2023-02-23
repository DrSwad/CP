#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

namespace Rho {
ull mul(ull a, ull b, ull mod) {
  ll ret = a * b - mod * (ull)(1.L / mod * a * b);
  return ret + mod * (ret < 0) - mod * (ret >= (ll)mod);
}

ull bigMod(ull a, ull e, ull mod) {
  ull ret = 1;
  while (e) {
    if (e & 1) {
      ret = mul(ret, a, mod);
    }
    a = mul(a, a, mod), e >>= 1;
  }
  return ret;
}

bool isPrime(ull n) {
  if (n < 2 or n % 6 % 4 != 1) {
    return (n | 1) == 3;
  }
  ull a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  ull s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull x : a) {
    ull p = bigMod(x % n, d, n), i = s;
    while (p != 1 and p != n - 1 and x % n and i--) {
      p = mul(p, p, n);
    }
    if (p != n - 1 and i != s) {
      return 0;
    }
  }
  return 1;
}

ull pollard(ull n) {
  auto f = [&](ull x) { return mul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 0, prod = 2, i = 1, q;
  while (t++ % 40 or __gcd(prod, n) == 1) {
    if (x == y) {
      x = ++i, y = f(x);
    }
    if ((q = mul(prod, max(x, y) - min(x, y), n))) {
      prod = q;
    }
    x = f(x), y = f(f(y));
  }
  return __gcd(prod, n);
}

vector<ull> factor(ull n) {
  if (n == 1) {
    return {};
  };
  if (isPrime(n)) {
    return {n};
  };
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}
}; // namespace Rho

__int128 binExp(__int128 a, __int128 e, __int128 m) {
  __int128 ret = 1;
  while (e) {
    if (e & 1) {
      ret = ret * a % m;
    }
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void print(__int128 x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    print(x / 10);
  }
  putchar(x % 10 + '0');
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<ll> a(n), b(m);
  for (ll &i : a) scanf("%lld", &i);
  for (ll &i : b) scanf("%lld", &i);

  map<ll, ll> primes;
  for (ll i : a) {
    vector<ull> v = Rho::factor(i);
    for (auto p : v) primes[p]++;
  }
  for (ll i : b) {
    vector<ull> v = Rho::factor(i);
    for (auto p : v) primes[p]--;
  }

  vector<pair<ll, ll>> A, B;
  for (auto [p, exp] : primes) {
    ll P = 1;
    for (int i = 0; i < abs(exp); i++) P *= p;
    if (exp < 0) B.push_back({p, P});
    else
      A.push_back({p, P});
  }

  int q;
  scanf("%d", &q);

  while (q--) {
    ll m;
    scanf("%lld", &m);

    vector<ull> v = Rho::factor(m);
    map<ll, bool> primes;
    for (auto p : v) primes[p] = true;
    ll phi = m;
    for (auto [p, ignore] : primes) {
      phi /= p;
      phi *= p - 1;
    }

    bool flag = true;
    __int128 ans = 1;
    for (auto [p, i] : A) ans = ans * (__int128)i % (__int128)m;
    for (auto [p, i] : B) {
      if (m % p == 0) {
        flag = false;
        break;
      }
      ans = ans * binExp(i, phi - 1, m) % (__int128)m;
    }

    if (!flag) {
      puts("DIVISION BY ZERO");
    } else {
      // __int128 L = 1, R = ans;
      // for (ll i : a) {
      //   L = L * (__int128)i % (__int128)m;
      // }
      // for (ll i : b) {
      //   R = R * (__int128)i % (__int128)m;
      // }
      // assert(L == R);
      print(ans);
      puts("");
    }
  }

  return 0;
}