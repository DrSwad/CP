template<class T>
class BIT2D {
public:
  int n, m;
  vector<BIT<T>> f;
  BIT2D(int n, int m) : n(n) {
    f.resize(n + 1, BIT<T>(m));
  }
  BIT2D(const vector<vector<T>> &grid) { // O(n^2 * log(n))
    n = grid.size();
    m = grid[0].size();
    vector<vector<T>> a(n + 1, vector<T>(m, (T)0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int fi = i + 1;
        while (fi <= n) {
          a[fi][j] += grid[i][j];
          fi += fi & -fi;
        }
      }
    }
    f.emplace_back(0);
    for (int i = 1; i <= n; i++) {
      f.emplace_back(BIT<T>(a[i]));
    }
  }
  void update(int p, int q, T v) {
    while (p <= n) f[p].update(q, v), p += p & -p;
  }
  T pref(int p, int q) {
    T ret = 0;
    while (p) ret += f[p].pref(q), p -= p & -p;
    return ret;
  }
  T range(int x1, int y1, int x2, int y2) {
    return pref(x2, y2) - pref(x2, y1 - 1) - pref(x1 - 1, y2) + pref(x1 - 1, y1 - 1);
  }
};