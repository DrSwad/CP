/**
 *    author:  tourist
 *    created: 29.08.2021 17:59:32
 **/
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<long long> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<long long> sa(n + 1);
  for (int i = 0; i < n; i++) {
    sa[i + 1] = sa[i] + a[i];
  }
  vector<long long> sb(n + 1);
  for (int i = 0; i < n; i++) {
    sb[i + 1] = sb[i] + b[i];
  }
  vector<long long> d(n + 1);
  for (int i = 0; i <= n; i++) {
    d[i] = sb[i] - sa[i];
  }
  SparseTable<long long> mn(d, [&](long long i, long long j) { return min(i, j); });
  SparseTable<long long> mx(d, [&](long long i, long long j) { return max(i, j); });
  for (int it = 0; it < q; it++) {
    int l, r;
    cin >> l >> r;
    --l;
    long long da = sa[r] - sa[l];
    long long db = sb[r] - sb[l];
    if (da != db) {
      cout << -1 << '\n';
      continue;
    }
    assert(d[l] == d[l]);
    long long L = mn.get(l, r);
    if (L < d[l]) {
      cout << -1 << '\n';
      continue;
    }
    cout << mx.get(l, r) - d[l] << '\n';
  }
  return 0;
}
