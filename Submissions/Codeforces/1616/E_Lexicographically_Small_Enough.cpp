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
  int n;
  cin >> n;

  string s, r;
  cin >> s >> r;

  vector<vector<int>> cpos(26);
  for (int i = 0; i < n; i++) {
    cpos[s[i] - 'a'].push_back(i);
  }
  for (int i = 0; i < 26; i++) {
    reverse(cpos[i].begin(), cpos[i].end());
  }

  SegmentTree<int> stree(vector<int>(n, 1), [&](int i, int j) {return i + j;}, [&](int i, int j) {return j;}, 0, true);

  long long ans = -1;
  long long moves = 0;

  for (int pos_r = 0; pos_r < n; pos_r++) {
    int cr = r[pos_r] - 'a';
    int pos_s = n;
    for (int i = 0; i < cr; i++) {
      if (!cpos[i].empty()) {
        pos_s = min(pos_s, cpos[i].back());
      }
    }

    if (pos_s < n) {
      long long nans = moves + stree.query(1, (pos_s + 1) - 1);
      ans = ans == -1 ? nans : min(ans, nans);
    }

    if (cpos[cr].empty()) break;
    pos_s = cpos[cr].back();
    cpos[cr].pop_back();
    moves += stree.query(1, (pos_s + 1) - 1);
    stree.update(pos_s + 1, 0);
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