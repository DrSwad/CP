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

void test_case() {
  int n, k;
  cin >> n >> k;

  map<int, int> freq;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    freq[a]++;
  }

  int sz = freq.size();
  vector<pair<int, int>> pp;
  for (auto [a, f] : freq) {
    pp.push_back({f, a});
  }
  sort(pp.begin(), pp.end());
  map<int, int> ids;
  vector<int> qq;
  for (auto [f, a] : pp) {
    int id = ids.size();
    ids[a] = id + 1;
    qq.push_back(f);
  }

  SegmentTree<int> st(qq, [&](int i, int j) {return i + j;}, [&](int i, int j) {return j;}, 0, true);
  SegmentTree<int> vis(vector<int>(sz, 1), [&](int i, int j) {return i + j;}, [&](int i, int j) {return j;}, 0, true);

  int blank = 0;
  int ans = n;
  for (int mex = 0; mex <= n; mex++) {
    int cf = 0;
    if (freq.find(mex) != freq.end()) {
      cf = freq[mex];
      st.update(ids[mex], 0);
      vis.update(ids[mex], 0);
    }

    if (cf > k or blank > k) continue;
    int have = k - cf;

    int L = 0, R = sz;
    while (L != R) {
      int mid = (L + R + 1) / 2;
      if (st.query(1, mid) <= have) L = mid;
      else R = mid - 1;
    }

    int index = vis.query(1, L);
    int diff = mex + (vis.query(1, sz) - index);
    ans = min(ans, diff - mex);

    if (cf == 0) blank++;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}