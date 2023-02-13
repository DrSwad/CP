#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> dp(n + 2, 0);
  dp[1] = 1;
  dp[2] = -1;

  for (int i = 1; i <= n; i++) {
    dp[i] += dp[i - 1];
    if (dp[i] >= m) dp[i] -= m;

    dp[i + 1] += dp[i];
    if (dp[i + 1] >= m) dp[i + 1] -= m;

    for (int j = 2 * i, q = 2; j <= n; j += i, q++) {
      dp[j] += dp[i];
      if (dp[j] >= m) dp[j] -= m;

      int r = min(n + 1, j + q);
      dp[r] -= dp[i];
      if (dp[r] < 0) dp[r] += m;
    }
  }

  printf("%d\n", dp[n]);

  return 0;
}