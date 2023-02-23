#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, d, m;
  cin >> n >> d >> m;

  vector<int> last(n, 0);
  vector<vector<int>> e(n);
  while (m--) {
    int u, v, d;
    cin >> u >> v >> d;
    u--, v--;
    last[u] = max(last[u], d);
    last[v] = max(last[v], d);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  for (int i = 0; i < n; i++) {
    vector<int> ne;
    vector<bool> vis(n, false);
    for (int j : e[i]) {
      if (!vis[j] and last[j] == last[i] + 1) {
        ne.push_back(j);
      }
    }
    e[i] = ne;
  }

  vector<bool> vis(n, false);
  function<void(int)> dfs = [&](int i) {
    if (vis[i]) return;
    vis[i] = true;
    for (int j : e[i]) if (!vis[j]) dfs(j);
  };

  for (int i = 0; i < n; i++) {
    if (last[i] == 1) dfs(i);
  }

  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (last[i] == d and vis[i]) {
      ans.push_back(i + 1);
    }
  }

  cout << ans.size() << "\n";
  for (int i : ans) cout << i << "\n";

  return 0;
}