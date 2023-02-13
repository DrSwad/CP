#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), p(n, -1) {}
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  bool merge(int a, int b, bool rank = true) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    if (rank and - p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  vector<int> sz(n, 1);
  DSU dsu(2 * n);

  for (int i = 0; i < n; i++) {
    dsu.merge(i, i + n, false);
  }

  int q;
  cin >> q;

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      if (sz[x] != 0 and sz[y] != 0 and s[x] != s[y]) {
        if (s[x] < s[y]) swap(x, y);
        sz[x] += sz[y];
        sz[y] = 0;
        s[x] += s[y];
        s[y] = 0;
        dsu.merge(x, y, false);
      }
    }
    else if (type == 2) {
      int x;
      cin >> x;
      x--;
      cout << sz[x] << "\n";
    }
    else if (type == 3) {
      int x;
      cin >> x;
      x--;
      cout << dsu.root(x) + 1 << "\n";
    }
  }
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