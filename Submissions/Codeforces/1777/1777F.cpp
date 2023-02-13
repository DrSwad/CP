#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges
#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 2;
  const int B = 30;
  int N;
  vector<vector<int>> next;
  vector<int> cnt;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    cnt.emplace_back(0);
    return N++;
  }

  inline void insert(int num) {
    int cur = 0;
    for (int i = B - 1; i >= 0; i--) {
      int to = num >> i & 1;
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }

  inline int find(int num) {
    int ans = 0;
    int cur = 0;
    for (int i = B - 1; i >= 0; i--) {
      int to = num >> i & 1;
      if (next[cur][to ^ 1] == -1) cur = next[cur][to];
      else {
        ans ^= 1 << i;
        cur = next[cur][to ^ 1];
      }
    }
    return ans;
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> l(n), r(n);

  for (int i = 0; i < n; i++) {
    l[i] = i - 1;
    while (l[i] >= 0) {
      if (a[l[i]] >= a[i]) break;
      l[i] = l[l[i]];
    }
  }
  for (int i = 0; i < n; i++) l[i] = i - l[i];

  for (int i = n - 1; i >= 0; i--) {
    r[i] = i + 1;
    while (r[i] < n) {
      if (a[r[i]] > a[i]) break;
      r[i] = r[r[i]];
    }
  }
  for (int i = 0; i < n; i++) r[i] = r[i] - i;

  vector<int> pref(n + 1);
  pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] ^ a[i - 1];
  }
  vector<int> suff(n + 1);
  suff[n] = 0;
  for (int i = n - 1; i >= 0; i--) {
    suff[i] = suff[i + 1] ^ a[i];
  }

  int blk = max(5, (int)sqrt(n));
  vector<vector<Trie>> blks(2);
  for (int mode = 0; mode < 2; mode++) {
    for (int i = 0; i <= n; i++) {
      if (i % blk == 0) blks[mode].push_back(Trie());
      blks[mode].back().insert(mode == 0 ? pref[i] : suff[i]);
    }
  }

  // 0 <= l, r <= n
  function<int(int, int, int, int)> query = [&](int mode, int l, int r, int xr) {
    int ret = 0;
    for (int i = l; i <= r; ) {
      if (i % blk == 0 and min(i + blk, n + 1) <= r + 1) {
        ret = max(ret, blks[mode][i / blk].find(xr));
        i += blk;
      }
      else {
        if (mode == 0) ret = max(ret, pref[i] ^ xr);
        else ret = max(ret, suff[i] ^ xr);
        i++;
      }
    }
    return ret;
  };

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (l[i] <= r[i]) {
      for (int j = i; j > i - l[i]; j--) {
        int xr = (pref[i] ^ pref[j]) ^ (a[i]) ^ (pref[i]);
        ans = max(ans, query(0, i + 1, i + r[i], xr));
      }
    }
    else {
      for (int j = i; j < i + r[i]; j++) {
        int xr = (suff[i + 1] ^ suff[j + 1]) ^ (a[i]) ^ (suff[i + 1]);
        ans = max(ans, query(1, i - l[i] + 1, i, xr));
      }
    }
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