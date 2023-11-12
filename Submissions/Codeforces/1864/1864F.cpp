#include <bits/stdc++.h>
using namespace std;

template<typename T, class F = function<T(const T&, const T&)>>
class SegmentTree {
  int n;
  vector<T> a;
  vector<T> st;
  T st_default;
  F merge;
  F setval;
  void build(int stI, int L, int R) {
    if (L == R) {
      st[stI] = a[L - 1];
      return;
    }

    int mid = (L + R) >> 1;
    build(stI << 1, L, mid);
    build(stI << 1 | 1, mid + 1, R);

    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }
  void update(int stI, int L, int R, int at, T val) {
    if (L == R) {
      st[stI] = setval(st[stI], val);
      return;
    }

    int mid = (L + R) >> 1;
    if (at <= mid) update(stI << 1, L, mid, at, val);
    else update(stI << 1 | 1, mid + 1, R, at, val);

    st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
  }
  T query(int stI, int L, int R, int l, int r) {
    if (l <= L && R <= r) return st[stI];

    int mid = (L + R) >> 1;
    if (r <= mid) return query(stI << 1, L, mid, l, r);
    else if (mid + 1 <= l) return query(stI << 1 | 1, mid + 1, R, l, r);
    else return merge(
        query(stI << 1, L, mid, l, mid),
        query(stI << 1 | 1, mid + 1, R, mid + 1, r)
    );
  }
public:
  SegmentTree(const vector<T> &_a, const F &_merge, const F &_setval, T st_default, bool build_init) {
    n = static_cast<int>(_a.size());
    a = _a;
    st.resize(4 * n + 1, st_default);
    this->st_default = st_default;
    merge = _merge;
    setval = _setval;
    if (build_init) build(1, 1, n);
  }
  T query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return st_default;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void update(int at, T val) { // at is 1-based index
    if (at < 1 || n < at) return;
    update(1, 1, n, at, val);
  }
};

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  void update(int p, T v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  SegmentTree<int> st(vector<int>(n, 0), [&](int i, int j) {return max(i, j);}, [&](int i, int j) {return j;}, 0, false);

  vector<vector<int>> pos(n);
  for (int i = 0; i < n; i++) {
    pos[a[i]].push_back(i);
  }

  vector<pair<int, int>> ranges;
  for (int val = 0; val < n; val++) {
    if (pos[val].empty()) continue;
    ranges.emplace_back(val + 1, val + 1);

    for (int i = 1; i < pos[val].size(); i++) {
      int r = pos[val][i];
      int l = pos[val][i - 1];
      int mx = st.query(l + 1, r + 1);
      ranges.emplace_back(mx, val + 1);
    }

    for (int i : pos[val]) {
      st.update(i + 1, val + 1);
    }
  }

  sort(
    ranges.begin(),
    ranges.end(),
    [&](const auto&i1, const auto&i2) {
      auto [l1, r1] = i1;
      auto [l2, r2] = i2;
      return r1 < r2;
    }
  );

  vector<tuple<int, int, int>> queries;

  for (int qi = 0; qi < q; qi++) {
    int ql, qr;
    cin >> ql >> qr;
    queries.emplace_back(ql, qr, qi);
  }

  sort(
    queries.begin(),
    queries.end(),
    [&](const auto&i1, const auto&i2) {
      auto [ql1, qr1, qi1] = i1;
      auto [ql2, qr2, qi2] = i2;
      return qr1 < qr2;
    }
  );

  vector<int> ans(q);
  BIT<int> bit(n);
  int range_i = 0;

  for (auto [ql, qr, qi] : queries) {
    while (range_i < ranges.size() and ranges[range_i].second <= qr) {
      bit.update(1, 1);
      if (ranges[range_i].first + 1 <= n) {
        bit.update(ranges[range_i].first + 1, -1);
      }
      range_i++;
    }
    ans[qi] = bit.pref(ql);
  }

  for (int qi = 0; qi < q; qi++) {
    cout << ans[qi] << "\n";
  }

  return 0;
}