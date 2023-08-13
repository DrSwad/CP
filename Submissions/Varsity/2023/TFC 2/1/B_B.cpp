#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
  }
};

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

void test_case() {
  int n, k;
  cin >> n >> k;

  Trie trie;
  while (n--) {
    string s;
    cin >> s;
    trie.insert(s);
  }

  vector<int> l(trie.N), r(trie.N);
  vector<int> leaves;
  vector<int> values;

  function<void(int)> dfs = [&](int at) {};
  dfs(0);

  SegmentTreeLazy<long long> st(
    a,
    [&](long long i, long long j) {return i + j;}, // queries sum of the numbers in the range
    [&](long long i, long long j) {return i * j;}, // multiplies range by a number in updates
    0, // default value of array should be 0
    1, // default value of lazy should be 1
    true); // needs to build the tree on initialization, since provided vector has non-default values
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}