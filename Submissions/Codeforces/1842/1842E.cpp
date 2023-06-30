#include <bits/stdc++.h>
using namespace std;

template<typename T, class F = function<T(const T&, const T&)>>
class SegmentTreeLazy {
private:
  int n;
  vector<T> a;
  vector<T> st, lz;
  T st_default, lz_default;
  F st_merge, lz_merge;

  void build(int stI, int L, int R) {
    if (L == R) return void(st[stI] = a[L - 1]);
    int mid = (L + R) >> 1;
    build(stI << 1, L, mid), build(stI << 1 | 1, mid + 1, R);
    st[stI] = st_merge(st[stI << 1], st[stI << 1 | 1]);
  }

  inline void push(int stI, int L, int R) {
    st[stI] = lz_merge(st[stI], lz[stI]);
    if (L != R) {
      lz[stI << 1] = lz_merge(lz[stI << 1], lz[stI]);
      lz[stI << 1 | 1] = lz_merge(lz[stI << 1 | 1], lz[stI]);
    }
    lz[stI] = lz_default;
  }

  void update(int stI, int L, int R, int l, int r, T val) {
    if (lz[stI] != lz_default) push(stI, L, R);
    if (r < L or R < l) return;
    if (l <= L && R <= r) {
      lz[stI] = lz_merge(lz[stI], val);
      return push(stI, L, R);
    }
    int mid = (L + R) >> 1;
    update(stI << 1, L, mid, l, r, val);
    update(stI << 1 | 1, mid + 1, R, l, r, val);
    st[stI] = st_merge(st[stI << 1], st[stI << 1 | 1]);
  }

  T query(int stI, int L, int R, int l, int r) {
    if (r < L or R < l) return st_default;
    if (lz[stI] != lz_default) push(stI, L, R);
    if (l <= L && R <= r) return st[stI];
    int mid = (L + R) >> 1;
    return st_merge(
      query(stI << 1, L, mid, l, r),
      query(stI << 1 | 1, mid + 1, R, l, r)
      );
  }

public:
  SegmentTreeLazy(const vector<T> &a, const F &st_merge, const F &lz_merge, T st_default, T lz_default, bool build_init) {
    n = static_cast<int>(a.size());
    this->a = a;
    st.resize(4 * n + 1, st_default);
    lz.resize(4 * n + 1, lz_default);
    this->st_default = st_default;
    this->lz_default = lz_default;
    this->st_merge = st_merge;
    this->lz_merge = lz_merge;
    if (build_init) build(1, 1, n);
  }
  T query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return st_default;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void update(int l, int r, T val) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return;
    l = max(l, 1); r = min(r, n);
    update(1, 1, n, l, r, val);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k, A;
  cin >> n >> k >> A;

  vector<tuple<int, int, int>> intervals;
  vector<vector<int>> intervals_at(k + 1);
  for (int i = 0; i < n; i++) {
    int x, y, c;
    cin >> x >> y >> c;
    intervals.emplace_back(x, k - y, c);
    intervals_at[x].emplace_back(i);
  }

  const long long INF = 1e18;
  SegmentTreeLazy<long long> st(
    vector<long long>(k + 2),
    [&](long long i, long long j) {return min(i, j);},
    [&](long long i, long long j) {return i + j;},
    INF,
    0,
    false);

  st.update(k + 2, k + 2, -INF);

  for (int at_x = k; at_x >= 0; at_x--) {
    for (int id : intervals_at[at_x]) {
      auto [x, y, c] = intervals[id];
      st.update(at_x + 2, y + 1, c);
    }

    st.update(at_x + 1, at_x + 1, -INF + st.query(at_x + 2, k + 2));

    st.update(at_x + 2, k + 2, A);
  }

  cout << st.query(1, 1) << "\n";

  return 0;
}