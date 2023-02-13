#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

int freq[N];
int mu[N];
ll f[N];
ll cnt_d[N];
ll ans[N];

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
      f[m] += (d == 1) * mu[q];
    }
  }
}

void precalculate_cnt_d() {
  for (int d = 1; d < N; d++) {
    ll cnt = 0;
    for (int m = d; m < N; m += d) {
      cnt += freq[m];
    }
    cnt_d[d] = cnt * (cnt - 1) * (cnt - 2) / 6;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  while (n--) {
    int a;
    cin >> a;
    freq[a]++;
  }

  // sum_g(gcd(i, j))
  // = sum_g(e(g) * cnt_g(g))
  // = sum_g(sum_d(f(d)) * cnt_g(g)) ... f(d) = sum_d2(e(d2) * mu(n / d2))
  // = sum_d(f(d) * cnt_d(d))

  precalculate_mu();
  precalculate_f();
  precalculate_cnt_d();

  ll ans = 0;
  for (int d = 1; d < N; d++) {
    ans += f[d] * cnt_d[d];
  }
  cout << ans << "\n";

  return 0;
}