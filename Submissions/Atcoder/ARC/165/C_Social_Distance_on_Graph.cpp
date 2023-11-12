#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  int size(int a) { return -p[root(a)]; }
  int size() { return sz; }
  bool merge(int a, int b, bool rank = true) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    sz--;
    if (rank and - p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n);
  vector<tuple<int, int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    auto & [w, u, v] = edges[i];
    cin >> u >> v >> w;
    u--, v--;
  }

  sort(edges.begin(), edges.end());

  for (int i = 0; i < m; i++) {
    auto [w, u, v] = edges[i];
    adj[u].push_back(i);
    adj[v].push_back(i);
  }

  int max_x = int(2e9);
  for (int u = 0; u < n; u++) {
    if (adj[u].size() >= 2) {
      max_x = min(max_x, get<0>(edges[adj[u][0]]) + get<0>(edges[adj[u][1]]));
    }
  }

  DSU dsu(n);

  int ans = max_x;
  vector<vector<int>> cur_adj(n);
  vector<int> color(n, -1);

  function<void(int, int)> dfs =
    [&](int at, int from) {
      color[at] ^= 1;
      for (int to : cur_adj[at]) {
        if (to != from) {
          dfs(to, at);
        }
      }
    };

  for (auto [w, u, v] : edges) {
    if (w > max_x) break;

    if (color[u] == -1) {
      if (color[v] == -1) {
        color[u] = 0, color[v] = 1;
      }
      else {
        color[u] = color[v] ^ 1;
      }
    }
    else if (color[v] == -1) {
      color[v] = color[u] ^ 1;
    }
    else if (color[u] == color[v]) {
      if (dsu.same(u, v)) {
        ans = w;
        break;
      }
      if (dsu.size(u) <= dsu.size(v)) dfs(u, -1);
      else dfs(v, -1);
    }

    if (!dsu.same(u, v)) {
      cur_adj[u].push_back(v);
      cur_adj[v].push_back(u);
      dsu.merge(u, v);
    }
  }

  cout << ans << "\n";

  return 0;
}