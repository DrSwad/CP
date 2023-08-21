#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int mod = int(1e9) + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int fact[N], inv[N], ifact[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i < N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);
}

int nCk(int n, int k) {
  if (k<0 or k> n) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int a, b, n;
  cin >> a >> b >> n;

  function<bool(int)> is_good =
    [&](int n) {
      while (n) {
        int d = n % 10;
        n /= 10;
        if (d != a and d != b) return false;
      }
      return true;
    };

  int ans = 0;
  for (int cnt_a = 0; cnt_a <= n; cnt_a++) {
    int cnt_b = n - cnt_a;
    int sum = cnt_a * a + cnt_b * b;
    if (is_good(sum)) {
      ans = add(ans, nCk(n, cnt_a));
    }
  }

  cout << ans << "\n";

  return 0;
}