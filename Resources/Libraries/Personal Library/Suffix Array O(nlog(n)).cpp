class SuffixArray {
  // Everything is 0-indexed
private:
  int n, logn;
  string s; // Suffix array will be built for this string
  vector<int> cnt, nxt; // Internal
  vector<bool> bh, b2h; // Internal
  vector<vector<int>> lcp_sparse; // lcp_sparse[i][j] = min(lcp[j], ..., lcp[j + (1 << i) - 1])
  bool lcp_built, lcp_sparse_built;

  void init() {
    cnt.resize(n, 0), nxt.resize(n, 0), bh.resize(n, 0), b2h.resize(n, 0), SA.resize(n, 0), iSA.resize(n, 0), lcp.resize(n, 0);
    lcp_sparse.resize(logn, vector<int>(n, 0));
    lcp_built = lcp_sparse_built = false;
  }

  void build_SA() {
    for (int i = 0; i < n; i++) SA[i] = i;
    sort(SA.begin(), SA.end(), [&](int i, int j) { return s[i] < s[j]; });

    for (int i = 0; i < n; i++) {
      bh[i] = i == 0 || s[SA[i]] != s[SA[i - 1]];
      b2h[i] = 0;
    }

    for (int h = 1; h < n; h <<= 1) {
      int tot = 0;
      for (int i = 0, j; i < n; i = j) {
        j = i + 1;
        while (j < n && !bh[j]) j++;
        nxt[i] = j; tot++;
      } if (tot == n) break;

      for (int i = 0; i < n; i = nxt[i]) {
        for (int j = i; j < nxt[i]; j++) iSA[SA[j]] = i;
        cnt[i] = 0;
      }

      cnt[iSA[n - h]]++;
      b2h[iSA[n - h]] = 1;
      for (int i = 0; i < n; i = nxt[i]) {
        for (int j = i; j < nxt[i]; j++) {
          int s = SA[j] - h;
          if (s < 0) continue;
          int head = iSA[s];
          iSA[s] = head + cnt[head]++;
          b2h[iSA[s]] = 1;
        }
        for (int j = i; j < nxt[i]; j++) {
          int s = SA[j] - h;
          if (s < 0 || !b2h[iSA[s]]) continue;
          for (int k = iSA[s] + 1; !bh[k] && b2h[k]; k++) b2h[k] = 0;
        }
      }
      for (int i = 0; i < n; i++) {
        SA[iSA[i]] = i;
        if (b2h[i]) bh[i] = true;
      }
    }
    for (int i = 0; i < n; i++) iSA[SA[i]] = i;
  }

  void build_lcp() {
    lcp_built = true;
    for (int i = 0, k = 0; i < n; i++) {
      if (iSA[i] == n - 1) {
        k = 0;
        lcp[n - 1] = 0;
        continue;
      }
      int j = SA[iSA[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      lcp[iSA[i]] = k;
      if (k) k--;
    }
  }

  void build_lcp_sparse() {
    if (!lcp_built) build_lcp();
    lcp_sparse_built = true;
    for (int i = 0; i < n; i++) lcp_sparse[0][i] = lcp[i];
    for (int i = 1; i < logn; i++) {
      for (int j = 0; j < n; j++) {
        lcp_sparse[i][j] = min(lcp_sparse[i - 1][j], lcp_sparse[i - 1][min(n - 1, j + (1 << (i - 1)))]);
      }
    }
  }

public:

  vector<int> SA, iSA; // SA is the suffix array, iSA[i] stores the rank of the i'th suffix
  vector<int> lcp; // Stores lcp of SA[i] and SA[i + 1]; lcp[n - 1] = 0

  // O(nlog(n))
  SuffixArray(string s) {
    n = s.length();
    logn = 32 - __builtin_clz(n);
    this->s = s;
    init();
    build_SA();
  }

  // Returns (l, r) such that l <= from <= r and lcp(SA[l], SA[r]) >= min_lcp
  // O(log(n))
  pair<int, int> min_lcp_range(int from, int min_lcp) {
    assert(0 <= from and from < n);
    assert(min_lcp <= n - SA[from]); // min_lcp should be >= length of the suffix
    if (!lcp_sparse_built) build_lcp_sparse();

    int r = from;
    for (int i = logn - 1; i >= 0; i--) {
      int jump = 1 << i;
      if (r + jump < n and lcp_sparse[i][r] >= min_lcp) r += jump;
    }

    int l = from;
    for (int i = logn - 1; i >= 0; i--) {
      int jump = 1 << i;
      if (l - jump >= 0 and lcp_sparse[i][l - jump] >= min_lcp) l -= jump;
    }

    return make_pair(l, r);
  }

  // Returns lcp(SA[l], SA[r - 1])
  // O(1)
  int range_lcp(int l, int r) {
    assert(0 <= l and l < r and r <= n);
    if (!lcp_sparse_built) build_lcp_sparse();
    int msb = 31 - __builtin_clz(r - l);
    return min(lcp_sparse[msb][l], lcp_sparse[msb][r - (1 << msb)]);
  }

  // Returns lcp of the suffixes s[i...n-1] and s[j...n-1]
  // O(1)
  int suffix_lcp(int i, int j) {
    if (i == j) return n - i;
    i = iSA[i], j = iSA[j];
    if (j < i) swap(i, j);
    return range_lcp(i, j);
  }

  // Compares the suffixes s[i...n-1] and s[j...n-1]
  // O(1)
  bool compare(int i, int j) {
    int len_i = n - i, len_j = n - j;
    int lcp = suffix_lcp(i, j);
    if (lcp >= len_i or lcp >= len_j) return len_i < len_j;
    return s[i + lcp] < s[j + lcp];
  }
};