#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> e(m);
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[i] = {u, v};
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  vector<bool> vis(m);
  vector<bool> node_vis(n);
  function<void(int)> dfs = [&](int at) {
    node_vis[at] = true;
    for (int ei : adj[at]) {
      int to = e[ei].first ^ e[ei].second ^ at;
      if (!vis[ei] and !node_vis[to]) {
        vis[ei] = true;
        dfs(to);
      }
    }
  };

  function<bool(int, int, int)> does_form_cycle = [&](int i, int j, int k) {
    auto [i1, i2] = e[i];
    auto [j1, j2] = e[j];
    auto [k1, k2] = e[k];

    if (i1 == j1) {}
    else if (i1 == j2) swap(j1, j2);
    else if (i2 == j1) swap(i1, i2);
    else if (i2 == j2) swap(i1, i2), swap(j1, j2);
    else return false;

    return (j2 == k1 and i2 == k2) or (i2 == k1 and j2 == k2);
  };

  for (int it = 0; it < 10; it++) {
    for (int i = 0; i < n; i++) {
      shuffle(adj[i].begin(), adj[i].end(), rng);
    }
    fill(vis.begin(), vis.end(), false);
    fill(node_vis.begin(), node_vis.end(), false);
    dfs(0);

    vector<int> unvis;
    for (int i = 0; i < m; i++) {
      if (!vis[i]) unvis.push_back(i);
    }
    if (unvis.size() < 3 or !does_form_cycle(unvis[0], unvis[1], unvis[2])) {
      for (int i = 0; i < m; i++) {
        cout << (vis[i] ? '1' : '0');
      }
      cout << "\n";
      return;
    }
  }

  for (int i = 0; i < m; i++) {
    cout << (vis[i] ? '1' : '0');
  }
  cout << "\n";
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