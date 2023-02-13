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

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> b(n);
  for (int &i : b) cin >> i;
  b.push_back(0);

  vector<pair<int, int>> e;
  vector<pair<int, int>> e_order;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e.emplace_back(u, v);
    e_order.emplace_back(min(b[u], b[v]), i);
  }
  e.emplace_back(0, n);
  e_order.emplace_back(0, m);
  n++, m++;

  sort(e_order.begin(), e_order.end(), greater<pair<int, int>>());
  // debug(e);
  // debug(e_order);

  sort(b.begin(), b.end(), greater<int>());
  DSU dsu(n);
  long long ans = 0;

  for (int oi = 0, bi = 0; oi < m; ) {
    int nxt_oi = oi;
    while (nxt_oi < m and e_order[nxt_oi].first == e_order[oi].first) nxt_oi++;

    int w = e_order[oi].first;
    while (bi < n and b[bi] >= w) ans += b[bi] - w, bi++;

    for (int i = oi; i < nxt_oi; i++) {
      auto [u, v] = e[e_order[i].second];
      dsu.merge(u, v);
    }

    int not_found = n - bi;
    int comp = dsu.size() - not_found;
    int diff = e_order[oi].first - (nxt_oi == m ? 0 : e_order[nxt_oi].first);
    ans += 1ll * comp * diff;

    oi = nxt_oi;
  }

  cout << ans << "\n";
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