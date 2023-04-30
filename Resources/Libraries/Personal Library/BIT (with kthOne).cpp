struct FenwickTree {
  int n, lg;
  vector<int> f, one;

  FenwickTree(int n = 0) : n(n) {
    f.resize(n + 1, 0), one.resize(n + 1, 0), lg = 0;
    while (2 << lg <= n) ++lg;
  }

  void update(int p, int v) {
    one[p] ^= 1;
    while (p <= n) f[p] += v, p += p & -p;
  }

  int pref(int p) {
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }

  inline int range(int l, int r) {
    return pref(r) - pref(l - 1);
  }

  int kthOne(int k) {
    assert(k > 0);
    for (int i = 0, j = lg; j >= 0; --j) {
      int cur = i | 1 << j;
      if (cur > n) continue;
      if (f[cur] == k and one[cur]) return cur;
      if (f[cur] < k) i = cur, k -= f[cur];
    }
    return -1;
  }
};