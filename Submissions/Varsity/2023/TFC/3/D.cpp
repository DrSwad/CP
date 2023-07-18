#include <bits/stdc++.h>
using namespace std;

// const int MX = 1 << 10;
const int MX = 1 << 2; // REMOVE

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> parent(n, -1);
  vector dp(n, vector(MX, 0));

  function<void(int, int, vector<int>&)> inner_dfs =
    [&](int at, int dist, vector<int>&dist_dp) {
      dist_dp[dist] += dp[at][dist];
      for (int to : adj[at]) {
        if (to != parent[at]) {
          inner_dfs(to, dist + 1, dist_dp);
        }
      }
    };

  function<void(int)> dfs =
    [&](int at) {
      // DB();
      // debug(at);

      for (int to : adj[at]) {
        if (to != parent[at]) {
          parent[to] = at;
          dfs(to);
          for (int xr = 0; xr < MX; xr++) {
            dp[at][xr] += dp[to][xr];
          }
        }
      }

      // debug(dp[at]);

      vector<int> dist_dp(MX, 0);
      for (int to : adj[at]) {
        if (to != parent[at]) {
          inner_dfs(to, 0, dist_dp);
        }
      }

      // debug(dist_dp);

      dp[at][a[at]] = a[at] + dp[at][0];
      for (int xr = 0; xr < MX; xr++) {
        if (xr != a[at]) {
          int dist = xr ^ a[at];
          dp[at][xr] = max(dp[at][xr], dist_dp[dist] + a[at]);
        }
      }

      // debug(dp[at]);
    };

  dfs(0);

  cout << dp[0][0] << "\n";

  return 0;
}