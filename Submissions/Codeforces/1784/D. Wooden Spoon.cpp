#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int fact[N + 1], ifact[N + 1], inv[N + 1];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i <= N; i++) inv[i] = mul(inv[mod % i], (mod - mod / i));
  for (int i = 1; i <= N; i++) fact[i] = mul(fact[i - 1], i);
  for (int i = 1; i <= N; i++) ifact[i] = mul(ifact[i - 1], inv[i]);
}

int C(int n, int k) {
  if (k < 0 or k > n) return 0;
  if (k == 0 or k == n) return 1;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n;
  cin >> n;

  int len = 1 << n;

  auto solve_suffix = [&](int at, int rem) {
    if (rem <= 1) return 1;
    int suffix_rem = (len - at) - (1 << (rem - 2));
    int suffix_need = (1 << (rem - 2)) - 1;
    return mul(mul(C(suffix_rem, suffix_need), fact[suffix_need + 1]), 2);
  };

  vector<int> pref_sum(n + 2, 0);
  pref_sum[0] = 1;

  for (int at = 1; at <= len; at++) {
    int ans = 0;

    for (int took = n + 1; took >= 0; took--) {
      int cur = 0;

      if ((at == 1 and took > 0) or (at > 1 and took > 1)) {
        cur = mul(pref_sum[took - 1], solve_suffix(at, (n + 1) - (took - 1)));
        if (took == n + 1) ans = cur;
      }

      pref_sum[took] = add(pref_sum[took], cur);
    }

    cout << ans << "\n";
  }

  return 0;
}
