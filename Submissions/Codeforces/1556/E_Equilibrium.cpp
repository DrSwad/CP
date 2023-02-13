#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
typedef long long ll;

int n, q;
int a0[N], b0[N];
int d[N], a[N], mp[N];
int till[N];
ll takes[N], carry[N];

template<typename T>
class segmentTree {
  int n;
  vector<T> a;
  vector<T> st;
  T st_default;
  T (*merge)(T, T);
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
      st[stI] = val;
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
  segmentTree(vector<T> _a, T(*_merge)(T, T), T st_default, bool build_init) {
    n = _a.size();
    a = _a;
    st.resize(4 * n + 1, st_default);
    this->st_default = st_default;
    merge = _merge;
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
  cin >> n >> q;

  for (int i = 1; i <= n; i++) scanf("%d", &a0[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b0[i]);
  for (int i = 1; i <= n; i++) {
    d[i] = b0[i] - a0[i];
  }

  int _n = n;
  for (int i = 1, at = 1, e = 1; at <= _n; i++, at++, e *= -1) {
    if (d[at] * e < 0) {
      a[i] = 0;
      i++;
      n++;
      e *= -1;
    }

    a[i] = d[at];
    mp[at] = i;
  }

  for (int i = 1; i <= n; i++) {
    till[i] = i;
    takes[i] = 0;
    carry[i] = a[i];
    while (carry[i] < 0 and till[i] > 0) {
      int prev = till[i] - 1;
      till[i] = till[prev];
      ll take = min(-carry[i], carry[prev]);
      takes[i] = max(takes[prev], takes[i]) + take;
      carry[i] += carry[prev];
    }
  }

  segmentTree<ll> stASum(vector<ll>(a + 1, a + n + 1), [](ll i, ll j) {return i + j;}, 0ll, true);
  segmentTree<ll> stTillMin(vector<ll>(till + 1, till + n + 1), [](ll i, ll j) {return min(i, j);}, N, true);
  segmentTree<ll> stTakesMax(vector<ll>(takes + 1, takes + n + 1), [](ll i, ll j) {return max(i, j);}, 0ll, true);

  while (q--) {
    int l, r;
    scanf("%d %d", &l, &r);
    l = mp[l];
    r = mp[r];

    if (stASum.query(l, r) != 0) puts("-1");
    else if (stTillMin.query(l, r) < l) puts("-1");
    else printf("%lld\n", stTakesMax.query(l, r));
  }

  return 0;
}