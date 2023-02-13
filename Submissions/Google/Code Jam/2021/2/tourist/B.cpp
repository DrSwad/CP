/**
 *    author:  tourist
 *    created: 15.05.2021 17:12:49       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  const int MAX = (int) 1e6 + 10;
  vector<int> dp(MAX, 1);
  for (int i = 1; i < MAX; i++) {
    for (int j = 2 * i + 1; j < MAX; j += i) {
      dp[j] = max(dp[j], dp[i] + 1);
    }
  }
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    int ans = 1;
    for (int x = 3; x <= n; x++) {
      if (n % x == 0) {
        ans = max(ans, dp[n / x]);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
