#include <bits/stdc++.h>
using namespace std;

const int K = 1000;
const int T = 100;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int dp[2 * K * T + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, k, t;
  cin >> a >> b >> k >> t;
  k *= 2;

  dp[0] = 1;
  int mx = 0;

  for (int i = 1; i <= t; i++) {
    mx += k;

    int window = 0;
    for (int j = mx - 1; j >= mx - k and j >= 0; j--) {
      window = add(window, dp[j]);
    }

    for (int j = mx; j >= 0; j--) {
      dp[j] = add(window, dp[j]);
      if (j > 0) window = add(window, mod - dp[j - 1]);
      if (j - 1 - k >= 0) window = add(window, dp[j - 1 - k]);
    }
  }

  for (int i = 1; i <= mx; i++) {
    dp[i] = add(dp[i], dp[i - 1]);
  }

  int ans = 0;
  for (int i = 0; i <= mx; i++) {
    int j = (i + a) - 1 - b;
    j = min(mx, j);
    if (j >= 0) {
      int cur = add(dp[i], mod - (i > 0 ? dp[i - 1] : 0));
      ans = add(ans, mul(dp[j], cur));
    }
  }

  cout << ans << "\n";

  return 0;
}