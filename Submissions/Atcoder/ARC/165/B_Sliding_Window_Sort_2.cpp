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
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  vector<int> left(n);
  left[0] = 0;
  for (int i = 1; i < n; i++) {
    if (p[i - 1] > p[i]) left[i] = i;
    else left[i] = left[i - 1];
  }

  for (int i = 0; i < n; i++) {
    if (i - left[i] + 1 >= k) {
      for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << p[i] + 1;
      }
      cout << "\n";
      return 0;
    }
  }

  SparseTable<int> mn(p, [&](int i, int j) { return min(i, j); });

  int st = -1;
  for (int i = n - 1; i >= 0; i--) {
    int left_max = (i - 1) - left[i - 1] + 1;
    int right = k - left_max;
    if (i + right - 1 <= n - 1 and p[i - 1] < mn.get(i, i + right - 1)) {
      st = left[i - 1];
      break;
    }
    else if (i == n - k) {
      st = i;
      break;
    }
  }
  assert(st != -1);
  assert(st <= n - k);

  sort(p.begin() + st, p.begin() + st + k);
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i] + 1;
  }
  cout << "\n";

  return 0;
}