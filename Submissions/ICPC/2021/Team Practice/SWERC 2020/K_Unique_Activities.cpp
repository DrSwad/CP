#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

char s[N];
int SA[N], iSA[N];
int cnt[N], nxt[N];
bool bh[N], b2h[N];
int lcp[N];

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
    while (i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
    lcp[iSA[i]] = k;
    if (k) k--;
  }
}

int main() {
  scanf("%s", s);
  int n = strlen(s);

  buildSA(n);
  buildLCP(n);

  vector<int> mat_pos(n, -1);
  for (int i = n - 1; i >= 0; i--) {
    int j = iSA[i];
    int mat = lcp[j];
    if (j > 0) mat = max(mat, lcp[j - 1]);
    mat_pos[mat] = i;
  }

  for (int mat = 0; mat < n; mat++) {
    int st = mat_pos[mat];
    int en = st + (mat + 1);
    if (st >= 0 and en <= n) {
      s[en] = '\0';
      printf("%s\n", s + st);
      break;
    }
  }

  return 0;
}