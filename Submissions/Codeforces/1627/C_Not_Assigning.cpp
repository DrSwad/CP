#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> adj(n);
  vector<pair<int, int>> e(n - 1);

  for (int i = 0; i < n - 1; i++) {
    auto & [u, v] = e[i];
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  vector<int> color(n - 1);
  bool possible = true;

  function<void(int, int, int)> dfs = [&](int at, int from, int prev_color) {
    if (adj[at].size() > 2) possible = false;
    for (int ei : adj[at]) {
      int to = e[ei].first + e[ei].second - at;
      if (to != from) {
        color[ei] = prev_color == 2 ? 3 : 2;
        dfs(to, at, color[ei]);
      }
    }
  };

  int root;
  for (root = 0; root < n; root++) {
    if (adj[root].size() == 1) break;
  }
  if (root == n) possible = false;

  if (possible) dfs(root, -1, -1);

  if (!possible) cout << "-1\n";
  else {
    for (int i = 0; i < n - 1; i++) {
      if (i) cout << " ";
      cout << color[i];
    }
    cout << "\n";
  }
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