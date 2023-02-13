#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int mu[N];
ll f[N];

void precalculate_mu() {
  // mu(n) = n is 1 ? 1 : n is prime ? -1 : -mu(n / smallest_prime_factor(n))
  mu[1] = 1;
  vector<int> primes;
  vector<bool> is_prime(N, true);
  for (int i = 2; i < N; i++) {
    if (is_prime[i]) {
      mu[i] = -1;
      primes.push_back(i);
    }

    for (int prime : primes) {
      int j = i * prime;
      if (j >= N) break;
      is_prime[j] = false;
      if (i % prime == 0) {
        mu[j] = 0;
        break;
      }
      else {
        mu[j] = -mu[i];
      }
    }
  }
}

void precalculate_f() {
  for (int d = 1; d < N; d++) {
    for (int m = d, q = 1; m < N; m += d, q++) {
      f[m] += d * mu[q];
    }
  }
}

void test_case() {
  int k;
  cin >> k;

  vector<int> n(k);
  for (int &i : n) cin >> i;

  // sum_g(gcd(i, j))
  // = sum_g(g * cnt_g(g))
  // = sum_g(sum_d(f(d)) * cnt_g(g)) ... f(d) = sum_d2(d2 * mu(n / d2))
  // = sum_d(f(d) * cnt_d(d))

  ll ans = 0;
  int mx_n = *max_element(n.begin(), n.end());
  for (int i = 1; i <= mx_n; i++) {
    ll cnt = 1;
    for (int nn : n) (cnt *= nn / i) %= MOD;
    (ans += f[i] * cnt) %= MOD;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  precalculate_mu();
  precalculate_f();

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}