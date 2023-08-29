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

  int n;
  cin >> n;

  vector<pair<int, int>> v(n);
  vector<int> coords;
  for (auto & [l, r] : v) {
    cin >> l >> r;
    r = l + r;
    coords.push_back(l);
    coords.push_back(r);
  }
  sort(coords.begin(), coords.end());
  coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
  for (auto & [l, r] : v) {
    l = lower_bound(coords.begin(), coords.end(), l) - coords.begin();
    r = lower_bound(coords.begin(), coords.end(), r) - coords.begin();
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      return make_pair(v[i].first, -v[i].second) < make_pair(v[j].first, -v[j].second);
    }
  );

  int sz = coords.size();
  SegmentTreeLazy<int> st(
    vector<int>(sz, -1),
    [&](int i, int j) {return max(i, j);}, // queries max of the numbers in the range
    [&](int i, int j) {return max(i, j);}, // maxifies range by a number in updates
    -1, // default value of array should be -1
    -1, // default value of lazy should be -1
    false); // does not need to build the tree on initialization, since provided vector has default values

  vector<int> ans(n);
  for (int i : order) {
    auto [l, r] = v[i];
    ans[i] = st.query(r + 1, sz) + 1;
    st.update(1, r + 1, ans[i]);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}