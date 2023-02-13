#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
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

  int ans = 0;
  vector<bool> vis(m, false);
  DSU dsu(m);

  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;

    if (k == 0) ans++;
    else {
      vector<int> v(k);
      for (int &i : v) cin >> i, i--, vis[i] = true;
      for (int j = 0; j < k - 1; j++) {
        dsu.merge(v[j], v[j + 1]);
      }
    }
  }

  int comps = dsu.size() - count(vis.begin(), vis.end(), false);
  if (comps) ans += comps - 1;
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}