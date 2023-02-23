#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int LOGN = 20;

char s[N];
int SA[N], iSA[N];
int cnt[N], nxt[N];
bool bh[N], b2h[N];
int lcp[N];
int lcpSparse[LOGN][N];

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
  // debug() << name(n) name(from) name(minLCP);

  int r = from;
  for (int i = LOGN - 1; i >= 0; i--) {
    int diff = (1 << i);
    if (r + diff >= n) continue;
    if (lcpSparse[i][r] >= minLCP) r += diff;
  }

  int l = from;
  for (int i = LOGN - 1; i >= 0; i--) {
    int diff = (1 << i);
    if (l - diff < 0) continue;
    if (lcpSparse[i][l - diff] >= minLCP) l -= diff;
  }

  return make_pair(l, r);
}

int tree[N << 1];
void update(int n, int p, int v) {
  for (tree[p += n] = v; p > 1; p >>= 1) {
    tree[p >> 1] = max(tree[p], tree[p ^ 1]);
  }
}
int query(int n, int l, int r) {
  int ret = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = max(ret, tree[l++]);
    if (r & 1) ret = max(ret, tree[--r]);
  }
  return ret;
}

int n;
int str_at[N];
int str_len[N];

int main() {
  scanf("%d", &n);

  int len = 0;
  char str[N];

  for (int i = 0; i < n; i++) {
    scanf("%s", str);
    str_at[i] = len;
    str_len[i] = strlen(str);
    for (int j = 0; j < str_len[i]; j++) {
      s[len++] = str[j];
    }
    s[len++] = '$';
  }

  buildSA(len);
  buildLCP(len);
  buildLCPSparse(len);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    if (str_len[i] != str_len[j]) return str_len[i] > str_len[j];
    else return iSA[str_at[i]] > iSA[str_at[j]];
  });

  // debug() << "SA";
  // for (int i = 0; i < len; i++) {
  //   debug() << name(i) name(s[i]) name(iSA[i]);
  // }

  // debug() << "Q";
  for (int id : order) {
    auto [l, r] = minLCPRange(len, iSA[str_at[id]], str_len[id]);
    int ans = query(len, l, r + 1) + 1;
    // debug() << name(id) name(l) name(r) name(ans);
    for (int i = str_at[id]; i < str_at[id] + str_len[id]; i++) {
      update(len, iSA[i], ans);
    }
  }

  printf("%d\n", query(len, 0, len));

  return 0;
}