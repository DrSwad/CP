#include <bits/stdc++.h>
using namespace std;

template<typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>&a, const F&f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};

void test_case() {
  int n, m, q;
  cin >> n >> m >> q;

  vector<int> p(n);
  iota(p.begin(), p.end(), 0);

  vector<vector<int>> comp(n);
  for (int i = 0; i < n; i++) comp[i].push_back(i);

  vector<int> min_k(n - 1);

  function<int(int)> root =
    [&](int v) {
      return p[v] == v ? v : root(p[v]);
    };

  function<void(int, int, int)> merge =
    [&](int u, int v, int k) {
      u = root(u);
      v = root(v);
      if (u == v) return;
      if (comp[u].size() < comp[v].size()) swap(u, v);

      while (!comp[v].empty()) {
        int i = comp[v].back();
        comp[v].pop_back();
        comp[u].push_back(i);
        if (i < n - 1 and root(i + 1) == u) min_k[i] = k;
        if (i > 0 and root(i - 1) == u) min_k[i - 1] = k;
      }
      p[v] = u;
    };

  for (int k = 0; k < m; k++) {
    int u, v;
    cin >> u >> v;
    merge(u - 1, v - 1, k + 1);
  }

  SparseTable<int> mx(min_k, [&](int i, int j) { return max(i, j); });

  while (q--) {
    int l, r;
    cin >> l >> r;
    l -= 1, r -= 2;

    if (l <= r) cout << mx.get(l, r);
    else cout << 0;
    if (q) cout << " ";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}