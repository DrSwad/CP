#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n, comp_cnt, bip_cnt;
  vector<int> p;
  vector<bool> is_bip;
  vector<bool> col;
  vector<vector<int>> comp;

  DSU(int n) {
    this->n = comp_cnt = bip_cnt = n;
    p.resize(n);
    iota(p.begin(), p.end(), 0);
    is_bip.resize(n, true);
    col.resize(n, 0);
    for (int i = 0; i < n; i++) comp.push_back({i});
  }

  int root(int a) { return p[a] == a ? a : (p[a] = root(p[a])); }

  void merge(int a, int b) {
    int ra = root(a), rb = root(b);

    if (ra == rb) {
      if (is_bip[ra] and col[a] == col[b]) {
        is_bip[ra] = false;
        bip_cnt--;
      }
      return;
    }

    comp_cnt--;
    if (comp[ra].size() < comp[rb].size()) swap(ra, rb);

    p[rb] = ra;

    if (is_bip[ra] or is_bip[rb]) bip_cnt--;
    if (!is_bip[ra] or !is_bip[rb]) is_bip[ra] = is_bip[rb] = false;

    if (is_bip[ra] and col[a] == col[b]) {
      for (int i : comp[rb]) col[i] = !col[i];
    }

    for (int i : comp[rb]) comp[ra].push_back(i);
    comp[rb].clear();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  DSU dsu(n);

  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    dsu.merge(u, v);
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      dsu.merge(u, v);
    }
    else {
      int k;
      cin >> k;
      if (k == 0) cout << dsu.comp_cnt << "\n";
      else {
        int bips = dsu.bip_cnt;
        int non_bips = dsu.comp_cnt - bips;
        cout << (1ll << k) * bips + (1ll << (k - 1)) * non_bips << "\n";
      }
    }
  }

  return 0;
}