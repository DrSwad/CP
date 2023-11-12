#include <bits/stdc++.h>
using namespace std;

const int dr[] = {+1, 0, -1, 0};
const int dc[] = {0, +1, 0, -1};

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
  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector adj_empty(rows * cols, set<pair<int, int>>());

  DSU dsu(rows * cols);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'W') {
        for (int dir = 0; dir < 4; dir++) {
          int nrow = row + dr[dir];
          int ncol = col + dc[dir];
          if (0 <= nrow and nrow < rows and
              0 <= ncol and ncol < cols and
              grid[nrow][ncol] == 'W'
          ) {
            dsu.merge(row * cols + col, nrow * cols + ncol);
          }
        }
      }
    }
  }

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == '.') {
        for (int dir = 0; dir < 4; dir++) {
          int nrow = row + dr[dir];
          int ncol = col + dc[dir];
          if (0 <= nrow and nrow < rows and
              0 <= ncol and ncol < cols and
              grid[nrow][ncol] == 'W'
          ) {
            adj_empty[dsu.root(nrow * cols + ncol)].emplace(row, col);
          }
        }

      }
    }
  }

  int ans = 0;
  map<int, int> move_score;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'W') {
        int id = dsu.root(row * cols + col);
        assert(!adj_empty[id].empty());
        if (adj_empty[id].size() == 1) {
          auto [nrow, ncol] = *adj_empty[id].begin();
          move_score[nrow * cols + ncol]++;
          ans = max(ans, move_score[nrow * cols + ncol]);
        }
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}