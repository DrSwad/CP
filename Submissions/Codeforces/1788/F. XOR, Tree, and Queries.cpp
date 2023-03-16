#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> parent(n);
  vector<int> parent_edge_id(n);
  vector<bool> taken(n, false);

  {
    vector<pair<int, int>> e(n - 1);
    vector<vector<int>> adj_e(n);
    for (int i = 0; i < n - 1; i++) {
      auto &[u, v] = e[i];
      cin >> u >> v;
      u--, v--;
      adj_e[u].push_back(i);
      adj_e[v].push_back(i);
    }

    function<void(int, int)> dfs = [&](int at, int from) {
      parent[at] = from;

      int child = 0;
      for (int to_e : adj_e[at]) {
        int to = e[to_e].first + e[to_e].second - at;
        if (to != from) {
          parent_edge_id[to] = to_e;
          dfs(to, at);
          child++;
        }
      }

      if (at > 0 and child % 2 == 0) {
        taken[at] = true;
      }
    };

    parent_edge_id[0] = -1;
    dfs(0, -1);
  }

  vector<vector<pair<int, int>>> adj_p(n);
  while (q--) {
    int u, v, x;
    cin >> u >> v >> x;
    u--, v--;
    adj_p[u].emplace_back(v, x);
    adj_p[v].emplace_back(u, x);
  }

  vector<bool> visited(n, false);
  function<int(int, int, vector<pair<int, int>>&)> dfs = [&](int at, int from, vector<pair<int, int>> &vals) {
    int val = vals.back().second;
    visited[at] = true;
    int ret = taken[at] ? val : 0;
    for (auto [to, xr] : adj_p[at]) {
      if (to != from and !visited[to]) {
        vals.emplace_back(to, val ^ xr);
        ret ^= dfs(to, at, vals);
      }
    }
    return ret;
  };

  vector<int> p(n, 0);
  int xr = 0;
  vector<pair<int, int>> alternate_vals;

  for (int root = 0; root < n; root++) {
    int cur_taken = 0;

    for (int val : {0, (1 << BITS) - 1}) {
      if (visited[root]) break;

      vector<pair<int, int>> vals;
      vals.emplace_back(root, val);
      int cur_xr = dfs(root, -1, vals);

      if (val == 0) {
        xr ^= cur_xr;
        for (auto [node, val] : vals) {
          p[node] = val;
          cur_taken += taken[node];
          visited[node] = false;
        }
      }
      else if (root != 0 and alternate_vals.empty() and cur_taken % 2 == 1) alternate_vals = vals;
    }
  }

  if (xr and !alternate_vals.empty()) {
    for (auto [node, val] : alternate_vals) {
      p[node] ^= xr;
    }
    xr = 0;
  }

  bool okay = true;
  for (int i = 0; i < n; i++) {
    for (auto [j, xr] : adj_p[i]) {
      if ((p[i] ^ p[j]) != xr) okay = false;
    }
  }

  if (!okay) cout << "No\n";
  else {
    vector<int> ans(n - 1);
    for (int i = 1; i < n; i++) {
      ans[parent_edge_id[i]] = (p[i] ^ p[parent[i]]);
    }

    cout << "Yes\n";
    for (int i = 0; i < n - 1; i++) {
      if (i) cout << " ";
      cout << ans[i];
    }
    cout << "\n";
  }

  return 0;
}
