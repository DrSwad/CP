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

void test_case() {
  int n, m;
  cin >> n >> m;

  DSU dsu(2 * n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    u *= 2, v *= 2;

    string s;
    cin >> s;

    int w = s == "imposter";

    dsu.merge(u + 0, v + w);
    dsu.merge(u + 1, v + (w ^ 1));
  }

  for (int i = 0; i < n; i++) {
    if (dsu.root(i << 1) == dsu.root(i << 1 | 1)) {
      cout << "-1\n";
      return;
    }
  }

  vector<int> cnt(2 * n, 0);
  for (int i = 0; i < n; i++) {
    cnt[dsu.root(i << 1)]++;
  }

  int ans = 0;
  vector<bool> vis(2 * n, false);

  for (int i = 0; i < n; i++) {
    int r[2] = {dsu.root(i << 1), dsu.root(i << 1 | 1)};
    if (!vis[r[0]] and !vis[r[1]]) {
      ans += max(cnt[r[0]], cnt[r[1]]);
      vis[r[0]] = vis[r[1]] = true;
    }
  }

  cout << ans << "\n";
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