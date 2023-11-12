#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
  int n;
  cin >> n;

  vector<int> h(n), a(n);
  for (int &i : h) cin >> i;
  for (int &i : a) cin >> i;

  int mx_a = *max_element(a.begin(), a.end());
  vector<pair<int, int>> mx_h(mx_a + 1, make_pair(-1, -1));

  function<void(int&, int&, int)> set_mx =
    [&](int &mx1, int &mx2, int cur) {
      if (cur == -1) return;
      if (cur == mx1 or cur == mx2) return;
      if (mx1 == -1 or h[cur] > h[mx1]) mx2 = mx1, mx1 = cur;
      else if (mx2 == -1 or h[cur] > h[mx2]) mx2 = cur;
    };

  for (int i = 0; i < n; i++) {
    auto & [mx1, mx2] = mx_h[a[i]];
    set_mx(mx1, mx2, i);
  }

  SparseTable<pair<int, int>> mx_st(mx_h, [&](pair<int, int> i, pair<int, int> j) {
      auto [mx11, mx12] = i;
      auto [mx21, mx22] = j;
      int mx1 = -1, mx2 = -1;
      set_mx(mx1, mx2, mx11);
      set_mx(mx1, mx2, mx12);
      set_mx(mx1, mx2, mx21);
      set_mx(mx1, mx2, mx22);
      return make_pair(mx1, mx2);
    });

  vector<ll> ans(n, 0ll);
  for (int x = 1; x <= mx_a; x++) {
    int mx1 = -1, mx2 = -1;
    ll val1 = -1, val2 = -1;
    for (int l = 1, q = 1; l <= mx_a; l += x, q++) {
      int r = min(mx_a, l + x - 1);
      auto [i1, i2] = mx_st.get(l, r);

      if (i1 != -1) {
        int i = i1;
        ll val = 1ll * q * h[i];
        if (val > val1) val2 = val1, mx2 = mx1, val1 = val, mx1 = i;
        else if (val > val2) val2 = val, mx2 = i;
      }

      if (i2 != -1) {
        int i = i2;
        ll val = 1ll * q * h[i];
        if (val > val1) val2 = val1, mx2 = mx1, val1 = val, mx1 = i;
        else if (val > val2) val2 = val, mx2 = i;
      }
    }

    if (mx1 != -1) {
      val2 = max(val2, 0ll);
      ans[mx1] = max(ans[mx1], val1 - val2);
    }
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
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