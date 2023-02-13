#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOGN = 18;

char s[N];
int SA[N], iSA[N];
int cnt[N], nxt[N];
bool bh[N], b2h[N];
int lcp[N];
int lcpSparse[LOGN][N];
int SASparse[LOGN][N];

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

void buildLCPSparse(int n) {
  for (int i = 0; i < n; i++) lcpSparse[0][i] = lcp[i];
  for (int i = 1; i < LOGN; i++) {
    for (int j = 0; j < n; j++) {
      lcpSparse[i][j] = min(lcpSparse[i - 1][j], lcpSparse[i - 1][min(n - 1, j + (1 << (i - 1)))]);
    }
  }
}

pair<int, int> minLCPRange(int n, int from, int minLCP) {
  int r = from;
  for (int i = LOGN - 1; i >= 0; i--) {
    int jump = 1 << i;
    if (r + jump < n and lcpSparse[i][r] >= minLCP) r += jump;
  }

  int l = from;
  for (int i = LOGN - 1; i >= 0; i--) {
    int jump = 1 << i;
    if (l - jump >= 0 and lcpSparse[i][l - jump] >= minLCP) l -= jump;
  }

  return make_pair(l, r);
}

void buildSASparse(int n) {
  for (int i = 0; i < n; i++) SASparse[0][i] = SA[i];
  for (int i = 1; i < LOGN; i++) {
    for (int j = 0; j < n; j++) {
      SASparse[i][j] = min(SASparse[i - 1][j], SASparse[i - 1][min(n - 1, j + (1 << (i - 1)))]);
    }
  }
}

int minSAQuery(int l, int r) { // [l, r]
  int lg = 32 - __builtin_clz(r - l + 1) - 1;
  return min(SASparse[lg][l], SASparse[lg][r - (1 << lg) + 1]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  fgets(s, N, stdin);
  {
    int len = strlen(s);
    while (s[len - 1] == '\n') s[len - 1] = '\0';
  }

  int n = strlen(s);
  buildSA(n);
  buildLCP(n);
  buildLCPSparse(n);
  buildSASparse(n);

  function<bool(int, int)> check = [&](int i, int len) {
    auto [l, r] = minLCPRange(n, iSA[i], len);
    int mn_i = minSAQuery(l, r);
    return mn_i < i;
  };

  vector<int> dp(n + 1);
  dp[n] = 0;

  for (int i = n - 1; i >= 0; i--) {
    int L = 0, R = n - i + 1;
    while (R - L > 1) {
      int M = (R + L) / 2;
      if (check(i, M)) L = M;
      else R = M;
    }

    dp[i] = dp[i + 1] + 1;
    if (L > 0) dp[i] = min(dp[i], 3 + dp[i + L]);
  }

  cout << dp[0] << "\n";

  return 0;
}