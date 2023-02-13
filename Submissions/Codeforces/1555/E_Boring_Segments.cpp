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

const int INF = 1e9;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> segs(n);
  map<int, int> coords;
  coords[1] = coords[m] = 0;

  for (auto & [l, r, w] : segs) {
    cin >> l >> r >> w;
    l++;
    coords[l - 1] = coords[l] = coords[r] = 0;
  }

  {
    int c = 0;
    for (auto & [x, y] : coords) {
      y = ++c;
    }
  }

  for (auto & [l, r, w] : segs) {
    l = coords[l];
    r = coords[r];
  }

  int C = coords.size();
  SegmentTreeLazy<int> st(vector<int>(C, 0),
                          [&](int i, int j) {return min(i, j);},
                          [&](int i, int j) {return max(i, j);},
                          INF,
                          0,
                          true);

  sort(segs.begin(), segs.end(), [&](const auto&s1, const auto&s2) {
    return get<2>(s1) < get<2>(s2);
  });

  int ans = INF;

  for (auto & [l, r, w] : segs) {
    st.update(l, r, w);
    int mn = st.query(2, C);
    if (mn > 0) ans = min(ans, w - mn);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}