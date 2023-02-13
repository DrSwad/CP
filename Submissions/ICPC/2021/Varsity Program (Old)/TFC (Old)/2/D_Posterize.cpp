#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int D = 256;
const ll INF = LLONG_MAX;

int d, k;
ll f[D];
ll dp_single[D][D];
ll dp[D][D][D];

ll DP(int k, int l, int r) {
  if (r - l + 1 <= k + 1) return 0;
  if (k == 0) return dp_single[l][r];
  if (dp[k][l][r] != -1) return dp[k][l][r];

  ll &ret = dp[k][l][r];
  ret = INF;
  for (int i = l; i <= r; i++) {
    int L = (k + 1) / 2, R = (k + 1) - L;
    ret = min(ret, DP(L - 1, l, i) + DP(R - 1, i + 1, r));
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> d >> k;

  for (int i = 0; i < d; i++) {
    int r; ll p;
    cin >> r >> p;
    f[r] = p;
  }

  for (int i = 0; i < D; i++) {
    ll p = 0;
    for (int l = i; l >= 0; l--) {
      p += f[l] * (i - l) * (i - l);
      for (int r = i; r < D; r++) {
        p += f[r] * (r - i) * (r - i);
        dp[i][l][r] = p;
      }
      for (int r = i; r < D; r++) {
        p -= f[r] * (r - i) * (r - i);
      }
    }
  }

  for (int l = 0; l < D; l++) {
    for (int r = l; r < D; r++) {
      dp_single[l][r] = INF;
      for (int i = l; i <= r; i++) {
        dp_single[l][r] = min(dp_single[l][r], dp[i][l][r]);
      }
    }
  }

  memset(dp, -1, sizeof dp);

  cout << DP(k - 1, 0, D - 1) << "\n";

  return 0;
}