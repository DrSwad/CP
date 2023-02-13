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

typedef long long ll;
const int N = 3e5 + 5;
const int M = 400;

int n;
int a[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  SegmentTree<pair<int, ll>> stree(vector<pair<int, ll>>(N, {0, 0}), [&](const auto&i, const auto&j) {return make_pair(i.first + j.first, i.second + j.second);}, [&](const auto&i, const auto&j) {return make_pair(i.first + j.first, i.second + j.second);}, make_pair(0, 0), false);
  vector<int> small_freq(M, 0);
  ll ans = 0;

  for (int nn = 1; nn <= n; nn++) {
    ll aa = a[nn];

    if (aa <= M) {
      for (int i = 1; i < nn; i++) {
        ans += a[nn] % a[i];
        ans += a[i] % a[nn];
      }
    }
    else {
      ans += stree.query(1, aa - 1).second;
      for (int i = 1; i <= M; i++) {
        ans += aa % i * small_freq[i - 1];
      }
      for (int q = 1; ; q++) {
        int st = max((ll)M + 1, aa / (q + 1) + 1);
        int en = aa / q;
        if (en <= M) break;
        auto [f, s] = stree.query(st, en);
        ans += aa * f - s * q;
      }

      ans += aa * stree.query(aa + 1, N).first;
      for (int mm = aa; mm < N; mm += aa) {
        auto [f, s] = stree.query(mm + 1, mm + aa - 1);
        ans += s - (ll)f * mm;
      }
    }

    if (nn > 1) cout << " ";
    cout << ans;

    stree.update(aa, make_pair(1, aa));
    if (aa <= M) small_freq[aa - 1]++;
  }
  cout << "\n";

  return 0;
}