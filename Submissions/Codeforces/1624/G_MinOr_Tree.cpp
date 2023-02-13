#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  int disallowed_mask = 0;

  vector<bool> vis(n);
  function<void(int)> dfs = [&](int at) {
    if (vis[at]) return;
    vis[at] = true;
    for (auto [to, w] : adj[at]) {
      if ((w & disallowed_mask) == 0) {
        dfs(to);
      }
    }
  };
  auto check = [&]() {
    fill(vis.begin(), vis.end(), false);
    dfs(0);
    return accumulate(vis.begin(), vis.end(), 0) == n;
  };

  for (int b = 29; b >= 0; b--) {
    disallowed_mask |= 1 << b;
    if (!check()) disallowed_mask -= 1 << b;
  }

  cout << (((1 << 30) - 1) - disallowed_mask) << endl;
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