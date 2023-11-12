#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  vector<int> sz(n, 1);
  vector adj(n, vector<pair<int, int>>());
  vector<ll> d(n, 0);

  int at_q;
  vector<int> vis(n, -1);

  function<void(int)> dfs =
    [&](int at) {
      vis[at] = at_q;
      for (auto [to, w] : adj[at]) {
        if (vis[to] != at_q) {
          d[to] = d[at] + w;
          dfs(to);
        }
      }
    };

  function<int(int)> root =
    [&](int v) {
      return p[v] == v ? v : root(p[v]);
    };

  function<bool(int, int, int)> merge =
    [&](int u, int v, int w) {
      // DB();
      // debug(u, v, w);

      int ru = root(u), rv = root(v);
      if (ru == rv) {
        return d[u] - d[v] == w;
      }

      if (sz[ru] < sz[rv]) {
        swap(u, v);
        swap(ru, rv);
        w = -w;
      }

      p[rv] = ru;
      sz[ru] += sz[rv];

      d[v] = d[u] - w;
      dfs(v);
      adj[u].emplace_back(v, -w);
      adj[v].emplace_back(u, w);

      return true;
    };

  bool first = true;

  for (at_q = 0; at_q < q; at_q++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;

    if (merge(u, v, w)) {
      if (!first) cout << " ";
      first = false;
      cout << at_q + 1;
    }
  }
  cout << "\n";

  return 0;
}