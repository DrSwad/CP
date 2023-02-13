#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int INF = int(1e9) + 5;

int n, l, k;
int d[N], a[N];
int dp[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> l >> k;
  for (int i = 0; i < n; i++) cin >> d[i];
  d[n] = l;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < N; i++) {
    for (int take = 0; take < N; take++) {
      dp[i][take] = INF;
    }
  }

  dp[0][0] = 0;

  for (int i = 0; i < n; i++) {
    // DB();
    // debug(i);
    for (int taken = 0; taken <= i; taken++) {
      // DB();
      // debug(taken, dp[i][taken]);

      int pref = 0;
      int total_taken = taken;

      for (int take = 0; take <= (n - 1 - i); take++) {
        int j = i + take + 1;
        pref += (d[j] - d[j - 1]) * a[i];
        dp[j][total_taken] = min(dp[j][total_taken], pref + dp[i][taken]);
        // debug(take, pref, j, total_taken, dp[j][total_taken]);
        total_taken++;
      }
    }
  }

  int ans = INF;
  for (int take = 0; take <= k; take++) {
    ans = min(ans, dp[n][take]);
  }
  cout << ans << "\n";

  return 0;
}