#include <bits/stdc++.h>
using namespace std;

const int A = 2;
const int BITS = 30;
const int MAX_N = 1e6 + 5;
int sz;
int nxt[MAX_N * 30][2];
int cnt[MAX_N * 30];
int pref[MAX_N];

int node() {
  return sz++;
}

inline void insert(int a) {
  int cur = 0;
  cnt[cur]++;
  for (int bit = BITS - 1; bit >= 0; bit--) {
    int to = a >> bit & 1;
    if (nxt[cur][to] == -1) nxt[cur][to] = node();
    cur = nxt[cur][to];
    cnt[cur]++;
  }
}

inline int query(int a, int k) {
  int ans = 0;
  int cur = 0;
  for (int bit = BITS - 1; bit >= 0; bit--) {
    if (cur == -1) break;
    int to1 = (a >> bit & 1) ^ 1;
    if (k >> bit & 1) cur = nxt[cur][to1];
    else {
      if (nxt[cur][to1] != -1) ans += cnt[nxt[cur][to1]];
      cur = nxt[cur][to1 ^ 1];
    }
  }
  if (cur != -1) ans += cnt[cur];
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  memset(nxt, -1, sizeof nxt);

  node();

  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    pref[i + 1] = pref[i] ^ a;
  }

  long long ans = 0;

  for (int i = n; i >= 0; i--) {
    ans += query(pref[i], k);
    insert(pref[i]);
  }

  cout << ans << "\n";

  return 0;
}