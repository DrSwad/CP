#include <bits/stdc++.h>
using namespace std;

const int M = 5e3;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

vector<int> primes;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int len = 1; len <= n; len++) {
    dp[len] = dp[len - 1];
    for (int p : primes) {
      if (p >= m) break;
      if (p > len) break;
      int nlen = max(0, len - (p + 1));
      dp[len] = add(dp[len], dp[nlen]);
    }
  }

  cout << dp[n] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<bool> is_prime(M + 1, true);
  for (int p = 2; p <= M; p++) {
    if (is_prime[p]) {
      primes.push_back(p);
      for (int q = 2 * p; q <= M; q += p) {
        is_prime[q] = false;
      }
    }
  }

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}