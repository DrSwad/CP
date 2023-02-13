#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int phi[N];
long long coprime_sum[N];
unsigned long long lcm_sum[N];

void precalculate_phi() {
  // phi(n) = n is 1 ? 1 : n is prime ? n - 1 : smallest_prime_factor(n) * phi(n / smallest_prime_factor(n))
  phi[1] = 1;
  vector<int> primes;
  vector<bool> is_prime(N, true);
  for (int i = 2; i < N; i++) {
    if (is_prime[i]) {
      phi[i] = i - 1;
      primes.push_back(i);
    }

    for (int prime : primes) {
      int j = i * prime;
      if (j >= N) break;
      is_prime[j] = false;
      if (i % prime == 0) {
        phi[j] = phi[i] * prime;
        break;
      }
      else {
        phi[j] = phi[i] * (prime - 1);
      }
    }
  }
}

void precalculate_coprime_sum() {
  coprime_sum[1] = coprime_sum[2] = 1;
  for (int i = 3; i < N; i++) {
    coprime_sum[i] = 1ll * phi[i] / 2 * i;
  }
}

void precalculate_lcm_sum() {
  precalculate_phi();
  precalculate_coprime_sum();

  for (int d = 1; d < N; d++) {
    for (int m = d, q = 1; m < N; m += d, q++) {
      lcm_sum[m] += coprime_sum[q] * m;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  precalculate_lcm_sum();

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    cout << lcm_sum[n] << "\n";
  }

  return 0;
}