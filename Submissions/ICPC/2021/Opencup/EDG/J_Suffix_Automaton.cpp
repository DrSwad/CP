#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

// Everything is 0-indexed
char s[N]; // Suffix array will be built for this string
int SA[N], iSA[N]; // SA is the suffix array, iSA[i] stores the rank of the i'th suffix
int cnt[N], nxt[N]; // Internal stuff
bool bh[N], b2h[N]; // Internal stuff
int lcp[N]; // Stores lcp of SA[i] and SA[i + 1]; lcp[n - 1] = 0

void buildSA(int n) {
  for (int i = 0; i < n; i++) SA[i] = i;
  sort(SA, SA + n, [](int i, int j) { return s[i] < s[j]; });

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
      bh[i] |= b2h[i];
    }
  }
  for (int i = 0; i < n; i++) iSA[SA[i]] = i;
}

void buildLCP(int n) {
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

int n;
int fsz[N];
ll len_freq[N];
void update_sz(int p, int v) {
  while (p <= n) fsz[p] += v, p += p & -p;
}
int pref_sz(int p) {
  int ret = 0;
  while (p) ret += fsz[p], p -= p & -p;
  return ret;
}

int q;
pair<int, int> vq[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  scanf("%s", s);
  n = strlen(s);

  buildSA(n);
  buildLCP(n);

  for (int i = 0; i < n; i++) {
    int l = (i == 0 ? 0 : lcp[i - 1]) + 1;
    int r = n - SA[i];
    if (r >= l) {
      update_sz(l, 1);
      if (r < n) update_sz(r + 1, -1);
    }
  }

  for (int len = 1; len <= n; len++) {
    len_freq[len] = len_freq[len - 1] + pref_sz(len);
  }

  cin >> q;
  for (int i = 0; i < q; i++) {
    ll k;
    cin >> k;
  }

  return 0;
}