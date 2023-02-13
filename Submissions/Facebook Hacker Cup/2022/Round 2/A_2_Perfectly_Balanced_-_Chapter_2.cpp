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
const int N = 1e6 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll mp[N];

void init() {
  unordered_map<ll, int> vis;
  uniform_int_distribution<ll> uid(1ll, (ll)1e12);
  auto gen = bind(uid, rng);
  for (int i = 1; i < N; i++) {
    ll val;
    do {
      val = gen();
    } while (vis.find(val) != vis.end());
    vis[val] = 1;
    mp[i] = val;
  }
}

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<ll> h(n);
  for (int i = 0; i < n; i++) {
    h[i] = mp[a[i]];
  }

  SegmentTree<ll> st_real(a, [&](ll i, ll j) {return i + j;}, [&](ll i, ll j) {return j;}, 0ll, true);
  SegmentTree<ll> st_hashed(h, [&](ll i, ll j) {return i + j;}, [&](ll i, ll j) {return j;}, 0ll, true);

  int q;
  cin >> q;

  int ans = 0;
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int at, val;
      cin >> at >> val;
      st_real.update(at, val);
      st_hashed.update(at, mp[val]);
    }
    else if (type == 2) {
      int l, r;
      cin >> l >> r;

      if ((r - l + 1) % 2 == 0) continue;
      int m = (l + r) / 2;

      bool possible = false;

      // middle
      {
        if (st_real.query(l, m - 1) == st_real.query(m + 1, r) and
            st_hashed.query(l, m - 1) == st_hashed.query(m + 1, r)
            ) {
          possible = true;
        }
      }

      // left
      if (r - l + 1 >= 3) {
        ll left_sum = st_real.query(l, m);
        ll right_sum = st_real.query(m + 1, r);
        ll val = left_sum - right_sum;
        if (1 <= val and val < N and
            st_hashed.query(l, m) - mp[val] == st_hashed.query(m + 1, r)
            ) {
          possible = true;
        }
      }

      // right
      if (r - l + 1 >= 3) {
        ll left_sum = st_real.query(l, m - 1);
        ll right_sum = st_real.query(m, r);
        ll val = right_sum - left_sum;
        if (1 <= val and val < N and
            st_hashed.query(l, m - 1) == st_hashed.query(m, r) - mp[val]
            ) {
          possible = true;
        }
      }

      ans += possible;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}