#include <bits/stdc++.h>
using namespace std;

class PalindromicTree {
private:
  int A;
  string s;
  int last, ptr;
  vector<int> link, len, occ, depth;
  vector<vector<int>> nxt;

  void init(int sz) {
    link.resize(sz, 0), len.resize(sz, 0), occ.resize(sz, 0), depth.resize(sz, 0);
    nxt.resize(sz, vector<int>(A, 0));
    len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  }

  void feed(int at) {
    while (s[at - len[last] - 1] != s[at]) last = link[last];
    int ch = s[at] - 'a', temp = link[last];
    while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
    if (!nxt[last][ch]) {
      nxt[last][ch] = ++ptr, len[ptr] = len[last] + 2;
      link[ptr] = len[ptr] == 1 ? 2 : nxt[temp][ch];
      depth[ptr] = depth[link[ptr]] + 1;
      palindromes.emplace_back(at - len[ptr], at);
    }
    last = nxt[last][ch], ++occ[last];
  }

public:
  vector<pair<int, int>> palindromes;

  PalindromicTree(string s, int A = 26) {
    int n = s.length();
    this->s = '0' + s;
    this->A = A;
    init(n + 3);
    for (int i = 1; i <= n; ++i) feed(i);
  }
};

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

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  string s;
  cin >> n >> s;

  PalindromicTree pt(s);
  SuffixArray sa(s);

  vector<pair<int, int>> palindromes = pt.palindromes;
  sort(
    palindromes.begin(),
    palindromes.end(),
    [&](const pair<int, int> &p1, const pair<int, int> &p2) {
    int len1 = p1.second - p1.first;
    int len2 = p2.second - p2.first;
    int lcp = sa.suffix_lcp(p1.first, p2.first);
    if (lcp >= len1 or lcp >= len2) return len1 < len2;
    return s[p1.first + lcp] < s[p2.first + lcp];
  }
    );

  vector<ll> pref;
  for (const pair<int, int> &p : palindromes) {
    pref.push_back((!pref.empty() ? pref.back() : 0) + p.second - p.first);
  }

  int q;
  cin >> q;

  while (q--) {
    ll l, r;
    cin >> l >> r;

    if (r > pref.back()) {
      cout << "-1\n";
      continue;
    }

    int pi = lower_bound(pref.begin(), pref.end(), l) - pref.begin();
    int i = palindromes[pi].first + ((l - 1) - (pi > 0 ? pref[pi - 1] : 0));
    ll rem = r - l + 1;

    while (rem) {
      if (i == palindromes[pi].second) {
        pi++;
        i = palindromes[pi].first;
      }
      cout << s[i];
      i++;
      rem--;
    }
    cout << "\n";
  }

  return 0;
}