#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
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

  int rows, cols;
  cin >> rows >> cols;

  DSU dsu(rows + cols);

  for (int r = 0; r < rows; r++) {
    string row;
    cin >> row;
    for (int c = 0; c < cols; c++) {
      if (row[c] == '#') {
        dsu.merge(r, rows + c);
      }
    }
  }

  dsu.merge(0, rows + 0);
  dsu.merge(0, rows + (cols - 1));
  dsu.merge(rows - 1, rows + 0);
  dsu.merge(rows - 1, rows + (cols - 1));

  int ans = INT_MAX;
  {
    set<int> st;
    for (int r = 0; r < rows; r++) {
      st.insert(dsu.root(r));
    }
    ans = min(ans, (int)st.size() - 1);
  }
  {
    set<int> st;
    for (int c = 0; c < cols; c++) {
      st.insert(dsu.root(rows + c));
    }
    ans = min(ans, (int)st.size() - 1);
  }

  cout << ans << "\n";

  return 0;
}