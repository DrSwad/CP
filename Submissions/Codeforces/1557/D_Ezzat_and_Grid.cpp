#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, m;
vector<pair<int, int>> row[N];
int from[N];

template<typename T, class F = function<T(const T&, const T&)>>
class SegmentTreeLazy {
private:
  int n;
  vector<T> a;
  vector<T> st, lz;
  T st_default, lz_default;
  F st_merge;
  F lz_merge;

  void build(int stI, int L, int R) {
    if (L == R) {
      st[stI] = a[L - 1];
      return;
    }

    int mid = (L + R) >> 1;
    build(stI << 1, L, mid);
    build(stI << 1 | 1, mid + 1, R);

    st[stI] = st_merge(st[stI << 1], st[stI << 1 | 1]);
  }

  void update(int stI, int L, int R, int l, int r, T val) {
    if (l <= L && R <= r) lz[stI] = lz_merge(lz[stI], val);
    else {
      int mid = (L + R) >> 1;
      if (l <= mid) update(stI << 1, L, mid, l, min(r, mid), val);
      if (mid + 1 <= r) update(stI << 1 | 1, mid + 1, R, max(l, mid + 1), r, val);
    }

    if (L == R) st[stI] = lz_merge(a[L - 1], lz[stI]);
    else st[stI] = lz_merge(st_merge(st[stI << 1], st[stI << 1 | 1]), lz[stI]);
  }

  T query(int stI, int L, int R, int l, int r) {
    if (l <= L && R <= r) return st[stI];

    int mid = (L + R) >> 1;
    if (r <= mid) return lz_merge(query(stI << 1, L, mid, l, r), lz[stI]);
    else if (mid + 1 <= l) return lz_merge(query(stI << 1 | 1, mid + 1, R, l, r), lz[stI]);
    else return st_merge(
        lz_merge(query(stI << 1, L, mid, l, mid), lz[stI]),
        lz_merge(query(stI << 1 | 1, mid + 1, R, mid + 1, r), lz[stI])
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
  cin.tie(0);

  cin >> n >> m;

  vector<int> coords;
  while (m--) {
    int i, l, r;
    cin >> i >> l >> r;
    row[i].push_back({l, r});
    coords.push_back(l);
    coords.push_back(r);
  }

  sort(coords.begin(), coords.end());
  coords.resize(unique(coords.begin(), coords.end()) - coords.begin());

  SegmentTreeLazy<pair<int, int>> st(vector<pair<int, int>>(coords.size(), make_pair(0, 0)),
                                     [&](pair<int, int> i, pair<int, int> j) {return max(i, j);},
                                     [&](pair<int, int> i, pair<int, int> j) {return max(i, j);},
                                     make_pair(0, 0),
                                     make_pair(0, 0),
                                     false);

  for (int i = 1; i <= n; i++) {
    sort(row[i].begin(), row[i].end());

    vector<pair<int, int>> nrow;

    int last_r = 0;
    for (auto [l, r] : row[i]) {
      l = upper_bound(coords.begin(), coords.end(), l) - coords.begin();
      r = upper_bound(coords.begin(), coords.end(), r) - coords.begin();

      if (r > last_r) {
        l = max(l, last_r + 1);
        nrow.push_back({l, r});
        last_r = r;
      }
    }

    row[i] = nrow;

    pair<int, int> mx(0, 0);
    for (auto [l, r] : row[i]) {
      mx = max(mx, st.query(l, r));
    }

    from[i] = mx.second;

    for (auto [l, r] : row[i]) {
      st.update(l, r, {mx.first + 1, i});
    }
  }

  auto ans = st.query(1, coords.size());
  cout << n - ans.first << endl;

  vector<int> vis(n + 1, true);
  for (int at = ans.second; at; at = from[at]) {
    vis[at] = false;
  }

  for (int i = 1; i <= n; i++) {
    if (vis[i]) cout << i << " ";
  }
  cout << endl;

  return 0;
}