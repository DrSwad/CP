#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d:\n", cs);

    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    vector<vector<int>> e(n), e2(n);
    vector<int> deg(n, 0);
    vector<vector<long long>> dp(n, vector<long long>(k + 1, -1));
    vector<bool> noOut(n);

    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--, v--;

      e[v].push_back(u);
      e2[u].push_back(v);
      e2[v].push_back(u);
      deg[u]++;
    }

    for (int i = 0; i < n; i++) { noOut[i] = deg[i] == 0; }

    queue<pair<int, int>> que;
    for (int i = 0; i <= k; i++) {
      dp[n - 1][i] = 0;
      que.push({n - 1, i});
    }

    while (!que.empty()) {
      auto [at, rem] = que.front();
      que.pop();

      if (rem == k) {
        if (noOut[at]) {
          for (int i = 0; i < k; i++) {
            if (dp[at][i] == -1) {
              dp[at][i] = dp[at][k] + 1;
              que.push({at, i});
            }
          }
        }

        for (int to : e[at]) {
          deg[to]--;
          if (deg[to] == 0) {
            dp[to][0] = dp[at][rem] + 1;
            que.push({to, 0});
            for (int i = 1; i <= k; i++) {
              if (dp[to][i] == -1) {
                dp[to][i] = dp[to][0];
                que.push({to, i});
              }
            }
          }
        }
      } else {
        for (int to : e2[at]) {
          if (dp[to][rem + 1] == -1) {
            dp[to][rem + 1] = dp[at][rem] + 1;
            que.push({to, rem + 1});
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      long long ans = -1;
      for (int j = 0; j <= k; j++) {
        if (dp[i][j] != -1) {
          ans = ans == -1 ? dp[i][j] : min(ans, dp[i][j]);
        }
      }
      printf("%lld\n", ans);
    }
  }

  return 0;
}