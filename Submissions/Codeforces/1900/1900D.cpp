#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());
  int mx_a = a.back();

  vector<vector<int>> pos(mx_a + 1);
  for (int i = 0; i < n; i++) {
    pos[a[i]].push_back(i);
  }

  vector<ll> dp(mx_a + 1);
  ll ans = 0;

  for (int g = mx_a; g >= 1; g--) {
    dp[g] = 0;

    for (int mul = g, prv = 0; mul <= mx_a; mul += g) {
      for (int i : pos[mul]) {
        dp[g] += 1ll * prv * (n - 1 - i);
        prv++;
      }
      if (mul > g) dp[g] -= dp[mul];
    }

    ans += dp[g] * g;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}