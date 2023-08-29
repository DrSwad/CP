#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, pos[2];
  cin >> n >> pos[0] >> pos[1];
  pos[0]--, pos[1]--;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> depth(n);
  function<void(int, int)> dfs1 =
    [&](int at, int from) {
      if (from != -1) depth[at] = depth[from] + 1;
      else depth[at] = 0;
      for (int to : adj[at]) {
        if (to != from) {
          dfs1(to, at);
        }
      }
    };
  dfs1(pos[1], -1);

  vector<pair<int, int>> leaves;
  function<void(int, int, int)> dfs2 =
    [&](int at, int from, int min_depth) {
      min_depth = min(min_depth, depth[at]);
      if (adj[at].size() == 1) {
        leaves.emplace_back(min_depth, depth[at] + depth[pos[0]] - 2 * min_depth);
      }
      for (int to : adj[at]) {
        if (to != from) {
          dfs2(to, at, min_depth);
        }
      }
    };
  dfs2(pos[0], -1, INT_MAX);

  int ans = 0;

  for (auto [min_depth, dist] : leaves) {
    int dist0 = depth[pos[0]] - min_depth;
    int dist1 = min_depth;
    if (dist0 < dist1) {
      int extra = dist1 - dist0;
      int moves = dist + (extra - 1);
      ans = max(ans, moves);
    }
  }

  cout << ans << "\n";

  return 0;
}