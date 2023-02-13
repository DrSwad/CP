#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges
#include <bits/stdc++.h>
using namespace std;

class SegmentTreeLazy {
private:
  int n;
  vector<int> a;
  vector<int> st;
  vector<bool> lz0, lz1;

  void build(int stI, int L, int R) {
    if (L == R) return void(st[stI] = a[L - 1]);
    int mid = (L + R) >> 1;
    build(stI << 1, L, mid), build(stI << 1 | 1, mid + 1, R);
    st[stI] = st[stI << 1] + st[stI << 1 | 1];
  }

  inline void push(int stI, int L, int R) {
    assert(!lz0[stI] or !lz1[stI]);
    if (lz0[stI]) {
      st[stI << 1] = 0;
      lz0[stI << 1] = true, lz1[stI << 1] = false;
      st[stI << 1 | 1] = 0;
      lz0[stI << 1 | 1] = true, lz1[stI << 1 | 1] = false;
    }
    else if (lz1[stI]) {
      int mid = (L + R) / 2;
      st[stI << 1] = mid - L + 1;
      lz0[stI << 1] = false, lz1[stI << 1] = true;
      st[stI << 1 | 1] = R - mid;
      lz0[stI << 1 | 1] = false, lz1[stI << 1 | 1] = true;
    }
    lz0[stI] = lz1[stI] = false;
  }

  void update(int stI, int L, int R, int l, int r, bool val) {
    if (lz0[stI] or lz1[stI]) push(stI, L, R);
    if (r < L or R < l) return;
    if (l <= L and R <= r) {
      if (!val) st[stI] = 0, lz0[stI] = true;
      else st[stI] = R - L + 1, lz1[stI] = true;
      return;
    }
    int mid = (L + R) >> 1;
    update(stI << 1, L, mid, l, r, val);
    update(stI << 1 | 1, mid + 1, R, l, r, val);
    st[stI] = st[stI << 1] + st[stI << 1 | 1];
  }

  int query(int stI, int L, int R, int l, int r) {
    if (r < L or R < l) return 0;
    if (lz0[stI] or lz1[stI]) push(stI, L, R);
    if (l <= L && R <= r) return st[stI];
    int mid = (L + R) >> 1;
    return query(stI << 1, L, mid, l, r) + query(stI << 1 | 1, mid + 1, R, l, r);
  }

public:
  SegmentTreeLazy(const vector<int> &a) {
    n = static_cast<int>(a.size());
    this->a = a;
    st.resize(8 * n + 1, 0);
    lz0.resize(8 * n + 1, false);
    lz1.resize(8 * n + 1, false);
    build(1, 1, n);
  }
  int query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return 0;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void update(int l, int r, bool val) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return;
    l = max(l, 1); r = min(r, n);
    update(1, 1, n, l, r, val);
  }
};

const int C = 26;

void test_case() {
  vector<string> s(2);
  cin >> s[0] >> s[1];

  vector<vector<SegmentTreeLazy>> st(2);
  for (int it = 0; it < 2; it++) {
    int n = s[it].length();
    for (int c = 0; c < C; c++) {
      vector<int> a(n, 0);
      for (int i = 0; i < n; i++) {
        a[i] = s[it][i] == 'a' + c;
      }
      st[it].push_back(SegmentTreeLazy(a));
    }
  }

  int m;
  cin >> m;

  while (m--) {
    int type;
    cin >> type;

    if (type == 1 or type == 2) {
      int id = type - 1;

      int l, r;
      cin >> l >> r;

      char ch;
      cin >> ch;
      int c;
      c = ch - 'a';

      for (int c = 0; c < C; c++) {
        st[id][c].update(l, r, false);
      }

      st[id][c].update(l, r, true);
    }
    else {
      int l1, r1, l2, r2;
      cin >> l1 >> r1 >> l2 >> r2;

      long long ans = r2 - l2 + 2;
      for (int c = 0; c < C; c++) {
        int cnt1 = st[0][c].query(l1, r1);
        int cnt2 = st[1][c].query(l2, r2);
        // debug(c, cnt1, cnt2);
        ans += 1ll * cnt1 * ((r2 - l2 + 2) - cnt2);
        // debug(ans);
      }

      cout << ans << "\n";
    }
  }
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