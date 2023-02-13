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
  int n, k;
  cin >> n >> k;

  vector<tuple<int, int, int>> mines(n);
  for (auto & [x, y, t] : mines) {
    cin >> x >> y >> t;
  }

  map<int, vector<int>> mines_at_x, mines_at_y;
  for (int i = 0; i < n; i++) {
    auto [x, y, t] = mines[i];
    mines_at_x[x].push_back(i);
    mines_at_y[y].push_back(i);
  }

  DSU dsu(n);

  for (auto [x, ids] : mines_at_x) {
    sort(
      ids.begin(),
      ids.end(),
      [&](int id1, int id2) {
      return get<1>(mines[id1]) < get<1>(mines[id2]);
    }
      );
    for (int i = 1; i < ids.size(); i++) {
      if (get<1>(mines[ids[i]]) - get<1>(mines[ids[i - 1]]) <= k) {
        dsu.merge(ids[i - 1], ids[i]);
      }
    }
  }
  for (auto & [y, ids] : mines_at_y) {
    sort(
      ids.begin(),
      ids.end(),
      [&](int id1, int id2) {
      return get<0>(mines[id1]) < get<0>(mines[id2]);
    }
      );
    for (int i = 1; i < ids.size(); i++) {
      if (get<0>(mines[ids[i]]) - get<0>(mines[ids[i - 1]]) <= k) {
        dsu.merge(ids[i - 1], ids[i]);
      }
    }
  }

  vector<vector<int>> groups = dsu.groups();
  vector<int> exp_t;
  for (auto &group : groups) {
    int mn = INT_MAX;
    for (int id : group) {
      mn = min(mn, get<2>(mines[id]));
    }
    exp_t.push_back(mn);
  }

  sort(exp_t.begin(), exp_t.end());

  int t = 0;
  for (int i = 0; i < exp_t.size(); t++) {
    while (i < exp_t.size() and exp_t[i] == t) i++;
    exp_t.pop_back();
  }

  cout << t - 1 << "\n";
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