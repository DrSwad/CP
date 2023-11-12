#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll a0 = 960002411612632915ll;
const ll mod = (ll)1e18 + 31;
const int root = 42;

namespace PollardRho {
  mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
  const int P = 1e6 + 9;
  ll seq[P];
  int primes[P], spf[P];
  inline ll add_mod(ll x, ll y, ll m) {
    return (x += y) < m ? x : x - m;
  }
  inline ll mul_mod(ll x, ll y, ll m) {
    ll res = __int128(x) * y % m;
    return res;
    // ll res = x * y - (ll)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
  }
  inline ll pow_mod(ll x, ll n, ll m) {
    ll res = 1 % m;
    for ( ; n; n >>= 1) {
      if (n & 1) res = mul_mod(res, x, m);
      x = mul_mod(x, x, m);
    }
    return res;
  }
  // O(it * (logn)^3), it = number of rounds performed
  inline bool miller_rabin(ll n) {
    if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
    if (n < P) return spf[n] == n;
    ll c, d, s = 0, r = n - 1;
    for ( ; !(r & 1); r >>= 1, s++) {}
    // each iteration is a round
    for (int i = 0; primes[i] < n && primes[i] < 32; i++) {
      c = pow_mod(primes[i], r, n);
      for (int j = 0; j < s; j++) {
        d = mul_mod(c, c, n);
        if (d == 1 && c != 1 && c != (n - 1)) return false;
        c = d;
      }
      if (c != 1) return false;
    }
    return true;
  }
  void init() {
    int cnt = 0;
    for (int i = 2; i < P; i++) {
      if (!spf[i]) primes[cnt++] = spf[i] = i;
      for (int j = 0, k; (k = i * primes[j]) < P; j++) {
        spf[k] = primes[j];
        if (spf[i] == spf[k]) break;
      }
    }
  }
  // returns O(n^(1/4))
  ll pollard_rho(ll n) {
    while (1) {
      ll x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
      ll *px = seq, *py = seq;
      while (1) {
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        if ((x = *px++) == y) break;
        v = u;
        u = mul_mod(u, abs(y - x), n);
        if (!u) return __gcd(v, n);
        if (++t == 32) {
          t = 0;
          if ((u = __gcd(u, n)) > 1 && u < n) return u;
        }
      }
      if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
    }
  }
  vector<ll> factorize(ll n) {
    if (n == 1) return vector<ll>();
    if (miller_rabin(n)) return vector<ll> {n};
    vector<ll> v, w;
    while (n > 1 && n < P) {
      v.push_back(spf[n]);
      n /= spf[n];
    }
    if (n >= P) {
      ll x = pollard_rho(n);
      v = factorize(x);
      w = factorize(n / x);
      v.insert(v.end(), w.begin(), w.end());
    }
    return v;
  }
}

ll get_phi(ll m) {
  if (m == mod) return mod - 1;

  vector<ll> facts = PollardRho::factorize(m);
  sort(facts.begin(), facts.end());
  ll ret = 1;

  for (int l = 0; l < facts.size(); ) {
    int r = l;
    ll p = facts[l];
    ll mul = 1;

    while (r < facts.size() and facts[l] == facts[r]) {
      r++;
      mul *= p;
    }

    ret *= mul - mul / p;
    l = r;
  }

  return ret;
}

ll add(ll a, ll b, ll m = mod) {
  ll c = a + b;
  return c < m ? c : c - m;
}

ll mul(ll a, ll b, ll m = mod) {
  return (__int128)a * b % m;
}

ll binExp(ll a, ll e, ll m = mod) {
  ll ret = 1 % m;
  while (e) {
    if (e & 1) ret = mul(ret, a, m);
    a = mul(a, a, m), e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  PollardRho::init();

  vector<ll> vals;
  map<ll, ll> phi;

  {
    queue<ll> q;
    q.push(mod);

    while (!q.empty()) {
      ll at = q.front();
      q.pop();

      vals.push_back(at);
      phi[at] = get_phi(at);

      if (find(vals.begin(), vals.end(), phi[at]) == vals.end()) {
        q.push(phi[at]);
      }
    }
  }

  sort(vals.begin(), vals.end());

  ll at = a0;
  ll len = 0;

  do {
    map<ll, ll> rem;

    for (ll val : vals) {
      if (val == 1) rem[val] = 0;
      else {
        if (gcd(root, val) == 1) rem[val] = binExp(root % val, rem[phi[val]], val);
        else if (at >= phi[val]) rem[val] = binExp(root % val, rem[phi[val]] + phi[val], val);
        else rem[val] = binExp(root % val, at, val);
      }
    }

    len++;
    at = rem[mod];

    if (len % 1000 == 0) {
      debug(len);
    }
  } while (at != a0);

  debug(len);

  return 0;
}