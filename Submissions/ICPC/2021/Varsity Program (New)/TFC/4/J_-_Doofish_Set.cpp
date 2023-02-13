#include <bits/stdc++.h>
using namespace std;

const int MAX_POWER = 1e6;

void impossible() {
  cout << "-1\n";
  exit(EXIT_SUCCESS);
}

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

  vector<vector<int>> adj(n);
  map<pair<int, int>, bool> evis;

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    if (a == b) impossible();
    if (a > b) swap(a, b);

    if (evis.find({a, b}) == evis.end()) {
      evis[{a, b}] = true;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
  }

  DSU dsu(n);

  for (int i = 0; i < n; i++) {
    sort(adj[i].begin(), adj[i].end());

    int mex = 0;
    for (int j : adj[i]) {
      if (j != mex) break;
      mex++;
    }

    if (i != mex) {
      dsu.merge(i, mex);
    }
  }

  vector<vector<int>> groups = dsu.groups();
  int gn = groups.size();
  vector<bool> group_vis(gn, false);
  int cnt = 0;

  for (int i = 0; i < n; i++) {
    for (int j : adj[i]) {
      if (dsu.same(i, j)) impossible();
      if (!group_vis[dsu.root(j)]) {
        cnt++;
        group_vis[dsu.root(j)] = true;
      }
    }

    if (cnt + 1 != gn) impossible();

    for (int j : adj[i]) {
      if (group_vis[dsu.root(j)]) {
        cnt--;
        group_vis[dsu.root(j)] = false;
      }
    }
  }

  int msb = 31 - __builtin_clz(gn - 1);
  cout << msb << "\n";

  if ((long long)n * msb > MAX_POWER) impossible();

  for (int move = 0; move < msb; move++) {
    vector<int> ans(n);
    for (int gi = 0; gi < gn; gi++) {
      for (int i : groups[gi]) {
        ans[i] = gi >> move & 1;
      }
    }

    for (int i : ans) cout << i;
    cout << "\n";
  }

  return 0;
}