#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = mul(fact[i - 1], i);
  }

  vector<int> dp(n + 1);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    dp[i] = mul(i, dp[i - 1]);
    dp[i] = add(dp[i], mul(fact[i - 1], mul(i, mul(i - 1, inv2))));
  }

  int ans = mul(2, dp[n]);
  ans = add(ans, mul(fact[n], mul(n, mul(n - 1, inv2))));

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}