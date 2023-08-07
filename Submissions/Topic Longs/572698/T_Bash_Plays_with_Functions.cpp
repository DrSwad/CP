#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
const int N = 1e6;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> sp(N + 1, -1);
  for (int p = 2; p <= N; p++) {
    if (sp[p] == -1) {
      sp[p] = p;
      for (int q = 2 * p; q <= N; q += p) {
        if (sp[q] == -1) {
          sp[q] = p;
        }
      }
    }
  }

  vector<int> fact(2 * N + 1), inv(2 * N + 1), ifact(2 * N + 1);
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i <= 2 * N; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i <= 2 * N; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i <= 2 * N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);

  // number of ways of writing n as a sum of k non-negative integers
  function<int(int, int)> n_sum_k =
    [&](int n, int k) {
      if (k == 0) return n == 0 ? 1 : 0;
      int up = n + k - 1;
      int down = k - 1;
      return mul(fact[up], mul(ifact[down], ifact[up - down]));
    };

  int q;
  cin >> q;

  while (q--) {
    int r, n;
    cin >> r >> n;

    int ans = 1;
    while (n > 1) {
      int p = sp[n];
      int exp = 0;
      int sum = 0;
      while (n % p == 0) {
        sum = add(sum, mul(2, n_sum_k(exp, r)));
        n /= p;
        exp++;
      }
      sum = add(sum, n_sum_k(exp, r));
      ans = mul(ans, sum);
    }

    cout << ans << "\n";
  }

  return 0;
}