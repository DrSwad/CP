#include <bits/stdc++.h>
using namespace std;

const int K = 17, N = 205;
const int INF = 1e9;

int n, k;
int a[N];
int dp[N][1 << K][2];
int inv[1 << K];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i]--;
  }

  for (int mask = 0; mask < 1 << k; mask++) {
    int zero = 0;
    for (int i = 0; i < k; i++) {
      if (mask >> i & 1) inv[mask] += zero;
      else zero++;
    }
  }

  for (int i = 0; i <= n + 1; i++) {
    for (int mask = 0; mask < 1 << k; mask++) {
      for (int it = 0; it < 2; it++) {
        dp[i][mask][it] = INF;
      }
    }
  }

  dp[0][0][0] = 0;
  for (int i = 1; i <= n; i++) {
    int v = a[i];

    for (int mask = 0; mask < 1 << k; mask++) {
      int &ans = dp[i][mask][0];
      ans = dp[i - 1][mask][0];

      if (mask >> v & 1) {
        int prv = dp[i - 1][mask ^ (1 << v)][0];

        if (prv < INF) {
          int bigger = __builtin_popcount(mask >> (v + 1));
          int smaller = __builtin_popcount(mask) - bigger - 1;
          int bits = smaller + 1 + bigger;
          int curr = bigger + prv + (bits - i);

          ans = min(ans, curr);
        }
      }
    }
  }

  dp[n + 1][0][1] = 0;
  for (int i = n; i >= 1; i--) {
    int v = a[i];

    for (int mask = 0; mask < 1 << k; mask++) {
      int &ans = dp[i][mask][1];
      ans = dp[i + 1][mask][1];

      if (mask >> v & 1) {
        int prv = dp[i + 1][mask ^ (1 << v)][1];

        if (prv < INF) {
          int bigger = __builtin_popcount(mask >> (v + 1));
          int smaller = __builtin_popcount(mask) - bigger - 1;
          int bits = smaller + 1 + bigger;
          int curr = smaller + prv + (i - bits);

          ans = min(ans, curr);
        }
      }
    }
  }

  int ans = INF;
  for (int i = 1; i <= n; i++) {
    int lbits = (k + 1) / 2;
    int rbits = k - lbits;

    for (int lmask = 0; lmask < 1 << k; lmask++) {
      if (__builtin_popcount(lmask) == lbits) {
        int rmask = ((1 << k) - 1) ^ lmask;
        int ldp = dp[i][lmask][0];
        int rdp = dp[i + 1][rmask][1];

        if (ldp < INF and rdp < INF) {
          int curr = ldp + rdp + inv[lmask] + lbits * (i - lbits) + rbits * -i;
          ans = min(ans, curr);
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}