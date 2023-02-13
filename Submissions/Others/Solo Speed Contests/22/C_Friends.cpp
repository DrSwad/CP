#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  int size(int a) { return -p[root(a)]; }
  bool merge(int a, int b) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    if (-p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
  vector<vector<int>> groups() {
    vector<int> _root(n), sz(n);
    for (int i = 0; i < n; i++) _root[i] = root(i), sz[_root[i]]++;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) g[i].reserve(sz[i]);
    for (int i = 0; i < n; i++) g[_root[i]].push_back(i);
    auto empty = [&](const vector<int>&v) { return v.empty(); };
    g.erase(remove_if(g.begin(), g.end(), empty), g.end());
    return g;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  DSU dsu(n);

  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    dsu.merge(u, v);
  }

  vector<vector<int>> groups = dsu.groups();

  int ans = 0;
  for (auto group : groups) {
    ans = max(ans, (int)group.size());
  }

  cout << ans << endl;

  return 0;
}