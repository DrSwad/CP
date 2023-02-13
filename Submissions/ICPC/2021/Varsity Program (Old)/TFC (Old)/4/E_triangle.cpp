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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<long long> a(n);
  for (long long &i : a) cin >> i;

  vector<int> b(n);
  iota(b.begin(), b.end(), 0);

  SegmentTree<int> st(
    b,
    [&](int i, int j) { return i == -1 ? j : j == -1 ? i : a[i] > a[j] ? i : j; },
    [&](int i, int j) {return j;},
    -1,
    true
    );

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int pos, val;
      cin >> pos >> val;
      // debug(t, pos, val);
      a[pos - 1] = val;
      st.update(pos, pos - 1);
      // debug(a);
    }
    else {
      int l, r;
      cin >> l >> r;
      // debug(t, l, r);

      vector<int> updates;
      int rem_try = 70;
      int m1 = -1, m2 = -1, m3 = -1;
      long long ans = 0;

      while (rem_try--) {
        m3 = m2;
        m2 = m1;
        m1 = st.query(l, r);
        if (m1 == -1) break;
        // debug(m1, a[m1], m2, m3);

        if (m2 != -1 and m3 != -1 and a[m1] + a[m2] > a[m3]) {
          // debug(a[m1], a[m2], a[m3]);
          ans = a[m1] + a[m2] + a[m3];
          break;
        }

        updates.push_back(m1);
        st.update(m1 + 1, -1);
      }

      cout << ans << "\n";

      for (int i = 0; i < updates.size(); i++) {
        st.update(updates[i] + 1, updates[i]);
      }
    }
  }

  return 0;
}