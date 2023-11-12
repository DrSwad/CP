#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

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
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  typedef pair<int, int> pii;
  vector<pii> v;
  for (int i = 0; i < n; i++) {
    v.emplace_back(a[i], -i);
  }
  SparseTable<pii> mx(v, [&](pii i, pii j) { return max(i, j); });

  function<vector<int>(int, int)> solve =
    [&](int l, int r) {
      if (l > r) return vector<int>(m + 1, 1);

      int mid = -mx.get(l, r).second;
      auto left = solve(l, mid - 1);
      auto right = solve(mid + 1, r);

      vector<int> cur(m + 1, 0);
      for (int val = 1; val <= m; val++) {
        cur[val] = add(cur[val - 1], mul(left[val - 1], right[val]));
      }
      return cur;
    };

  cout << solve(0, n - 1)[m] << "\n";
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