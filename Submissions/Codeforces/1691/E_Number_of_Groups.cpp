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
  int n;
  cin >> n;

  vector<int> c(n), l(n), r(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i] >> l[i] >> r[i];
  }

  vector<int> coords;
  for (int i : l) coords.push_back(i);
  for (int i : r) coords.push_back(i);
  sort(coords.begin(), coords.end());
  coords.resize(unique(coords.begin(), coords.end()) - coords.begin());

  for (int &i : l) i = lower_bound(coords.begin(), coords.end(), i) - coords.begin();
  for (int &i : r) i = lower_bound(coords.begin(), coords.end(), i) - coords.begin();

  int sz = coords.size();
  vector<vector<int>> ins_at(sz), rem_at(sz);
  for (int i = 0; i < n; i++) {
    ins_at[l[i]].push_back(i);
    rem_at[r[i]].push_back(i);
  }

  DSU dsu(n);
  map<int, int> grp_freq[2];

  for (int at = 0; at < sz; at++) {
    for (int i : ins_at[at]) {
      int cc = c[i];

      if (grp_freq[cc].empty()) {
        vector<int> ids;
        int tot_freq = 0;
        for (auto [id, freq] : grp_freq[cc ^ 1]) {
          ids.push_back(id);
          tot_freq += freq;
        }
        if (ids.size() >= 1) {
          for (int id : ids) {
            dsu.merge(id, ids[0]);
          }
          dsu.merge(i, ids[0]);

          grp_freq[cc ^ 1].clear();
          grp_freq[cc ^ 1][dsu.root(ids[0])] = tot_freq;
        }

        grp_freq[cc][dsu.root(i)] = 1;
      }
      else if (!grp_freq[cc ^ 1].empty()) {
        auto [id, freq] = *grp_freq[cc].begin();
        grp_freq[cc].clear();
        dsu.merge(i, id);
        grp_freq[cc][dsu.root(i)] = freq + 1;
      }
      else {
        grp_freq[cc][dsu.root(i)] = 1;
      }
    }

    for (int i : rem_at[at]) {
      int cc = c[i];

      int root = dsu.root(i);
      grp_freq[cc][root]--;
      if (grp_freq[cc][root] == 0) {
        grp_freq[cc].erase(root);
      }
    }
  }

  cout << dsu.size() << "\n";
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