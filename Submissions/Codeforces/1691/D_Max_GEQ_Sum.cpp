#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MX = 1e9;

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
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  a.insert(a.begin(), MX + 1);
  a.push_back(MX + 1);
  n += 2;

  vector<ll> pref;
  pref.push_back(a[0]);
  for (int i = 1; i < n; i++) {
    pref.push_back(pref.back() + a[i]);
  }

  vector<int> mx_l(n), mx_r(n);
  mx_l[0] = -1;
  for (int i = 1; i < n; i++) {
    mx_l[i] = i - 1;
    while (mx_l[i] > -1 and a[mx_l[i]] <= a[i]) {
      mx_l[i] = mx_l[mx_l[i]];
    }
  }
  mx_r[n - 1] = n;
  for (int i = n - 2; i >= 0; i--) {
    mx_r[i] = i + 1;
    while (mx_r[i] < n and a[mx_r[i]] <= a[i]) {
      mx_r[i] = mx_r[mx_r[i]];
    }
  }

  SegmentTree<ll> st_mn(pref, [&](ll i, ll j) {return min(i, j);}, [&](ll i, ll j) {return j;}, LLONG_MAX, true);
  SegmentTree<ll> st_mx(pref, [&](ll i, ll j) {return max(i, j);}, [&](ll i, ll j) {return j;}, LLONG_MIN, true);

  bool ans = true;
  for (int i = 1; i < n - 1; i++) {
    ll ls = pref[i - 1] - st_mn.query(mx_l[i] + 1, (i - 1) + 1);
    ll rs = st_mx.query(i + 1, (mx_r[i] - 1) + 1) - pref[i];
    ans = ans and ls + rs <= 0;
  }

  cout << (ans ? "YES" : "NO") << "\n";
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