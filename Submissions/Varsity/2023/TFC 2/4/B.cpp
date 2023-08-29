#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll extended_euclid(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extended_euclid(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
ll inverse(ll a, ll m) {
  ll x, y;
  ll g = extended_euclid(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

using T = __int128;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
T extended_euclid(T a, T b, T &x, T &y) {
  T xx = y = 0;
  T yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = extended_euclid(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  T m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

void test_case() {
  int n, m, q;
  cin >> n >> m >> q;

  if (m == 1) {
    while (q--) {
      int r;
      cin >> r;
      cout << "0\n";
    }
    return;
  }

  vector<int> primes;
  vector<bool> is_prime(n + 1, true);

  for (int p = 2; p <= n; p++) {
    if (is_prime[p]) {
      primes.push_back(p);
      for (int mul = 2 * p; mul <= n; mul += p) {
        is_prime[mul] = false;
      }
    }
  }

  vector<int> fact_m, fact_m_pow;
  vector<int> banned_primes;
  for (int p : primes) {
    if (m % p == 0) {
      int exp = 0;
      fact_m_pow.push_back(1);
      while (m % p == 0) {
        m /= p;
        exp++;
        fact_m_pow.back() *= p;
      }
      banned_primes.push_back(p);
      fact_m.push_back(exp);
    }
  }
  int rest_m = m;

  int sz = banned_primes.size();
  vector<vector<ll>> cnt(sz, vector<ll>(n + 1));
  vector<vector<ll>> unbanned_ans(sz, vector<ll>(n + 1));
  vector<ll> rest_ans(n + 1);

  rest_ans[0] = 1 % rest_m;
  for (int at = 1; at <= n; at++) {
    rest_ans[at] = rest_ans[at - 1] * at % rest_m;
  }

  for (int i = 0; i < sz; i++) {
    int p = banned_primes[i];
    cnt[i][0] = 0;
    unbanned_ans[i][0] = 1;
    int mul_freq = 0; // freq of p in 1*2*...*at
    int unbanned_mul = 0; // 1*2*...*at removing all p

    for (int at = 1; at <= n; at++) {
      int exp = 0;
      int val = at;
      while (val % p == 0) {
        val /= p;
        exp++;
      }
      mul_freq += exp;
      cnt[i][at] = cnt[i][at - 1] + mul_freq;
      unbanned_ans[i][at] = unbanned_ans[i][at - 1] * val % fact_m_pow[i];
    }
  }

  while (q--) {
    int r;
    cin >> r;

    vector<pair<int, int>> rems;
    for (int i = 0; i < sz; i++) {
      int p = banned_primes[i];
      ll exp = cnt[i][n] - cnt[i][r] - cnt[i][n - r];
      int m_exp = fact_m[i];
      if (exp >= m_exp) rems.emplace_back(fact_m_pow[i], 0);
      else {
        ll mod = fact_m_pow[i];
        for (int j = 0; j < m_exp - exp; j++) mod /= p;
        ll rem = unbanned_ans[i][n] * inverse(unbanned_ans[i][r], mod) % mod * inverse(unbanned_ans[i][n - r], mod) % mod;
        rems.emplace_back(fact_m_pow[i], rem * fact_m_pow[i] / mod);
      }
    }
    if (rest_m > 1) {
      ll mod = rest_m;
      ll rem = rest_ans[n] * inverse(rest_ans[r], mod) % mod * inverse(rest_ans[n - r], mod) % mod;
      rems.emplace_back(mod, rem);
    }

    if (rems.size() == 1) cout << rems[0].second << "\n";
    else {
      auto [rem, mod] = CRT(rems[0].second, rems[0].first, rems[1].second, rems[1].first);
      for (int i = 2; i < rems.size(); i++) {
        for (auto [_mod, _rem] : rems) {
          auto got = CRT(rem, mod, _rem, _mod);
          rem = got.first;
          mod = got.second;
        }
      }
      cout << (ll)rem << '\n';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}