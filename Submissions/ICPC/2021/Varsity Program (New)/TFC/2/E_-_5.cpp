#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> e(n);

  vector<bool> blocked(n, false);
  function<void(int)> block = [&](int i) {
    if (blocked[i]) return;
    blocked[i] = true;
    for (auto j : e[i]) block(j);
  };

  vector<int> col(n, -1);
  function<void(int, int)> color = [&](int i, int c) {
    if (col[i] == c) return;
    col[i] = c;
    for (int j : e[i]) {
      color(j, c ^ 1);
    }
  };

  DSU dsu(n);

  while (m--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x, c;
      cin >> x >> c;
      x--;
      a[x] = c;
    }
    else if (t == 2) {
      int x, y;
      cin >> x >> y;
      x--, y--;

      if (blocked[x]) block(y);
      else if (blocked[y]) block(x);
      // else {
      if (col[y] == -1) swap(x, y);
      if (col[y] == -1) col[x] = 0, col[y] = 1;
      else if (col[x] == -1) col[x] = col[y] ^ 1;
      else if (col[x] == col[y]) {
        if (dsu.same(x, y)) block(x), block(y);
        else {
          if (dsu.size(x) < dsu.size(y)) swap(x, y);
          color(y, col[x] ^ 1);
        }
      }

      dsu.merge(x, y);
      e[x].push_back(y);
      e[y].push_back(x);
      // }
    }
    else {
      int x, y, v;
      cin >> x >> y >> v;
      x--, y--;

      if (blocked[y] or !dsu.same(x, y)) cout << "0\n";
      else {
        ll num = (ll)a[x] * v;
        ll den = a[y];
        ll d = __gcd(num, den);
        num /= d;
        den /= d;
        if (col[x] != col[y]) num = -num;
        cout << num << "/" << den << "\n";
      }
    }
  }

  return 0;
}