#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
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
  ll k;
  cin >> n >> m >> k;

  vector<tuple<int, int, ll>> edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    u--, v--;
    edges.emplace_back(u, v, w);
  }

  ll min_cost = LLONG_MAX;

  for (int mask = 0; mask < 1 << m; mask++) {
    if (__builtin_popcount(mask) == n - 1) {
      DSU dsu(n);
      ll sum = 0;

      for (int j = 0; j < m; j++) {
        if (mask >> j & 1) {
          auto [u, v, w] = edges[j];
          dsu.merge(u, v);
          sum += w;
        }
      }

      if (dsu.size() == 1) {
        min_cost = min(min_cost, sum % k);
      }
    }
  }

  cout << min_cost << "\n";

  return 0;
}