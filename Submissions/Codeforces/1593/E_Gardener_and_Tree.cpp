#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<vector<int>> e(n);
  vector<int> deg(n, 0);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
    deg[u]++, deg[v]++;
  }

  set<pair<int, int>> vis;
  for (int i = 0; i < n; i++) {
    vis.insert({deg[i], i});
  }

  while (k--) {
    if (vis.empty()) break;

    vector<int> leaves;
    for (auto [d, u] : vis) {
      if (d > 1) break;
      leaves.push_back(u);
    }

    for (int u : leaves) {
      vis.erase({deg[u], u});
      for (int v : e[u]) {
        if (vis.find({deg[v], v}) != vis.end()) {
          vis.erase({deg[v], v});
          deg[v]--;
          vis.insert({deg[v], v});
        }
      }
    }
  }

  cout << vis.size() << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}