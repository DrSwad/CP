#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  int n, k, d;
  cin >> n >> k >> d;

  vector inv(k + 1, 0);
  inv[1] = 1;
  for (int i = 2; i <= k; i++) {
    inv[i] = mul(inv[mod % i], mod - mod / i);
  }

  vector<int> h(n);
  for (int &i : h) cin >> i;

  int mx = max(*max_element(h.begin(), h.end()), d);

  vector freq(mx + 1, 0);
  for (int i : h) freq[i]++;

  vector dp(mx + 1, 0);
  int ans = 0;

  for (int g = mx; g >= 1; g--) {
    int cnt = freq[g];
    for (int mul = 2 * g; mul <= mx; mul += g) {
      dp[g] = add(dp[g], mod - dp[mul]);
      cnt += freq[mul];
    }

    int ways = 1;
    for (int i = 0; i < k; i++) {
      ways = mul(ways, cnt - i);
      ways = mul(ways, inv[i + 1]);
    }

    dp[g] = add(dp[g], ways);

    if (d % g == 0) {
      ans = add(ans, dp[g]);
    }
  }

  for (int i = 1; i <= k; i++) {
    ans = mul(ans, i);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}