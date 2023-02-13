#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, l;
  cin >> n >> m >> l;

  vector<vector<int>> e(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
  }

  vector<bool> vis(n, false);

  function<void(int)> dfs = [&](int v) {
    vis[v] = true;
    for (int u : e[v]) {
      if (!vis[u]) {
        dfs(u);
      }
    }
  };

  while (l--) {
    int v;
    cin >> v;
    v--;
    dfs(v);
  }

  cout << accumulate(vis.begin(), vis.end(), 0) << "\n";
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