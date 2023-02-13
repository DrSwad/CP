#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 55;

int n, k;
vector<ll> vw;
ll a, b;

ll go(int n, int k, ll up) {
  if (!k) {
    return 0;
  }

  ll sum = 0;
  for (int i = 0; i < k - 1; i++) {
    sum += vw[i];
  }
  if (sum + vw[k - 1] > up) {
    return 0;
  }

  int take;
  for (take = k - 1; take < n; take++) {
    if (vw[take] + sum > up) break;
  }
  take--;

  return (1ll << take) | go(take, k - 1, up - vw[take]);
}

ll num[2];
ll dp[2][N][N][2];
ll DP(int dpi, int n, int k, bool flag) {
  if (k > n) {
    return 0;
  }
  if (k == 0) {
    return 1;
  }
  if (~dp[dpi][n][k][flag]) {
    return dp[dpi][n][k][flag];
  }

  if (flag) {
    dp[dpi][n][k][flag] =
        DP(dpi, n - 1, k, true) + DP(dpi, n - 1, k - 1, true);
  } else {
    bool has = num[dpi] >> (n - 1) & 1;
    dp[dpi][n][k][flag] = DP(dpi, n - 1, k, has);
    if (has) {
      dp[dpi][n][k][flag] += DP(dpi, n - 1, k - 1, false);
    }
  }

  return dp[dpi][n][k][flag];
}

int main() {
  cin >> n >> k;

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    ll w;
    cin >> w;
    vw.push_back(w);
    sum += w;
  }

  cin >> a >> b;

  if (sum < a) {
    puts("0");
    return 0;
  }

  sort(vw.begin(), vw.end());

  sum = 0;
  for (int i = 0; i < k; i++) {
    sum += vw[i];
  }
  if (sum > b) {
    puts("0");
    return 0;
  }

  if (k > n) {
    puts("0");
    return 0;
  }

  num[1] = go(n, k, b);
  num[0] = go(n, k, a - 1);
  memset(dp, -1, sizeof dp);

  cout << DP(1, n, k, false) - DP(0, n, k, false) << endl;

  return 0;
}