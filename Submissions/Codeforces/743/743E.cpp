#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
const int A = 8;

int n;
int a[N];
int nxt[A][N + 1][N + 1];
int dp[1 << A][N + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], a[i]--;

  for (int val = 0; val < A; val++) {
    nxt[val][n][0] = n - 1;
    for (int need = 1; need <= n; need++) {
      nxt[val][n][need] = n;
    }

    for (int pos = n - 1; pos >= 0; pos--) {
      nxt[val][pos][0] = pos - 1;
      for (int need = 1; need <= n; need++) {
        if (a[pos] == val) nxt[val][pos][need] = nxt[val][pos + 1][need - 1];
        else nxt[val][pos][need] = nxt[val][pos + 1][need];
      }
    }
  }

  for (int mask = 0; mask < 1 << A; mask++) {
    for (int need = 0; need <= n; need++) {
      if (mask == 0) {
        if (need == 0) dp[mask][need] = -1;
        else dp[mask][need] = n;
      }
      else {
        int cnt = __builtin_popcount(mask);
        int mn, mx;
        if (need % cnt == 0) mn = mx = need / cnt;
        else mn = need / cnt, mx = mn + 1;

        dp[mask][need] = n;

        for (int last = 0; last < A; last++) {
          if ((mask >> last & 1) == 0) continue;
          int pmask = mask ^ 1 << last;
          if (dp[pmask][need - mn] < n) {
            dp[mask][need] = min(dp[mask][need], nxt[last][dp[pmask][need - mn] + 1][mn]);
          }
          if (dp[pmask][need - mx] < n) {
            dp[mask][need] = min(dp[mask][need], nxt[last][dp[pmask][need - mx] + 1][mx]);
          }
        }
      }
    }
  }

  int ans = 0;
  for (int need = 1; need <= n; need++) {
    if (dp[(1 << A) - 1][need] < n) ans = need;
  }

  cout << ans << "\n";

  return 0;
}