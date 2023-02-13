#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<vector<int>> dp(n, vector<int>(n, 0));
  int ans = 0;
  for (int l = 0; l < n; l++) {
    for (int r = n - 1; r > l; r--) {
      if (r + 1 < n) dp[l][r] = max(dp[l][r], dp[l][r + 1]);
      if (l - 1 >= 0) dp[l][r] = max(dp[l][r], dp[l - 1][r]);
      if (s[l] == s[r]) {
        dp[l][r] = max(dp[l][r], 1);
        if (r + 1 < n and l - 1 >= 0) {
          dp[l][r] = max(dp[l][r], 1 + dp[l - 1][r + 1]);
        }
      }
      ans = max(ans, dp[l][r]);
    }
  }

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