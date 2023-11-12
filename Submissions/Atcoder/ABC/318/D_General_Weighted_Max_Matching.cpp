#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector w(n, vector(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      cin >> w[i][j];
    }
  }

  vector dp(1 << n, 0ll);
  long long ans = 0;

  for (int mask = 0; mask < 1 << n; mask++) {
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        for (int j = i + 1; j < n; j++) {
          if (mask >> j & 1) {
            int rest = mask - (1 << i) - (1 << j);
            dp[mask] = max(dp[mask], dp[rest] + w[i][j]);
          }
        }
      }
    }
    ans = max(ans, dp[mask]);
  }

  cout << ans << "\n";

  return 0;
}