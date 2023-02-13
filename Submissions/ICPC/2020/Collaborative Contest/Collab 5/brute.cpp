#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

namespace rho {
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXP = 1000010;
const int BASE[] = {2, 450775, 1795265022, 9780504, 28178, 9375, 325};

ll seq[MAXP];
int primes[MAXP], spf[MAXP];

inline ll mod_add(__int128 x, __int128 y, __int128 m) {
  __int128 z = x + y;
  return z < m ? z : z - m;
}

inline ll mod_mul(__int128 x, __int128 y, __int128 m) {
  return x * y % m;
}

inline ll mod_pow(ll x, ll n, ll m) {
  ll res = 1 % m;
  for (; n; n >>= 1) {
    if (n & 1) {
      res = mod_mul(res, x, m);
    }
    x = mod_mul(x, x, m);
  }
  return res;
}

/// O(k logn logn logn), k = number of rounds performed
inline bool miller_rabin(ll n) {
  if (n <= 2 || (n & 1 ^ 1)) {
    return (n == 2);
  }
  if (n < MAXP) {
    return spf[n] == n;
  }

  ll c, d, s = 0, r = n - 1;
  for (; !(r & 1); r >>= 1, s++) {
  }

  /// each iteration is a round
  for (int i = 0; primes[i] < n && primes[i] < 32; i++) {
    c = mod_pow(primes[i], r, n);
    for (int j = 0; j < s; j++) {
      d = mod_mul(c, c, n);
      if (d == 1 && c != 1 && c != (n - 1)) {
        return false;
      }
      c = d;
    }
    if (c != 1) {
      return false;
    }
  }
  return true;
}

inline void init() {
  int i, j, k, cnt = 0;
  for (i = 2; i < MAXP; i++) {
    if (!spf[i]) {
      primes[cnt++] = spf[i] = i;
    }
    for (j = 0, k; (k = i * primes[j]) < MAXP; j++) {
      spf[k] = primes[j];
      if (spf[i] == spf[k]) {
        break;
      }
    }
  }
}

/// Expected complexity O(n^(1/4))
ll pollard_rho(ll n) {
  while (1) {
    ll x = rand() % n, y = x, c = rand() % n, u = 1, v, t = 0;
    ll *px = seq, *py = seq;

    while (1) {
      *py++ = y = mod_add(mod_mul(y, y, n), c, n);
      *py++ = y = mod_add(mod_mul(y, y, n), c, n);
      if ((x = *px++) == y) {
        break;
      }

      v = u;
      u = mod_mul(u, abs(y - x), n);

      if (!u) {
        return __gcd(v, n);
      }
      if (++t == 32) {
        t = 0;
        if ((u = __gcd(u, n)) > 1 && u < n) {
          return u;
        }
      }
    }

    if (t && (u = __gcd(u, n)) > 1 && u < n) {
      return u;
    }
  }
}

vector<ll> factorize(ll n) {
  if (n == 1) {
    return vector<ll>();
  }
  if (miller_rabin(n)) return vector<ll>{n};

  vector<ll> v, w;
  while (n > 1 && n < MAXP) {
    v.push_back(spf[n]);
    n /= spf[n];
  }

  if (n >= MAXP) {
    ll x = pollard_rho(n);
    v = factorize(x);
    w = factorize(n / x);
    v.insert(v.end(), w.begin(), w.end());
  }

  sort(v.begin(), v.end());
  return v;
}
} // namespace rho

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
  rho::init();

  int n, m;
  scanf("%d %d", &n, &m);

  vector<ll> a(n), b(m);
  for (ll &i : a) scanf("%lld", &i);
  for (ll &i : b) scanf("%lld", &i);

  map<ll, int> primes;
  for (ll i : a) {
    vector<ll> v = rho::factorize(i);
    for (auto p : v) primes[p]++;
  }
  for (ll i : b) {
    vector<ll> v = rho::factorize(i);
    for (auto p : v) primes[p]--;
  }

  a.clear();
  b.clear();
  for (auto [p, exp] : primes) {
    ll P = 1;
    for (int i = 0; i < abs(exp); i++) P *= p;
    if (exp < 0) b.push_back(P);
    else
      a.push_back(P);
  }

  int q;
  scanf("%d", &q);

  while (q--) {
    ll m;
    scanf("%lld", &m);

    vector<ll> v = rho::factorize(m);
    map<ll, bool> primes;
    for (auto p : v) primes[p] = true;
    ll phi = m;
    for (auto [p, ignore] : primes) {
      phi /= p;
      phi *= p - 1;
    }

    bool flag = true;
    __int128 ans = 1;
    for (ll i : a) ans = ans * (__int128)i % (__int128)m;
    for (ll i : b) {
      if (gcd(i, m) != 1) {
        flag = false;
        break;
      }
      ans = ans * binExp(i, phi - 1, m) % (__int128)m;
    }

    if (!flag) {
      puts("DIVISION BY ZERO");
    } else {
      print(ans);
      puts("");
    }
  }

  return 0;
}