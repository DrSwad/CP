#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 1e6 + 5;

long long dp[N][4];

long long DP(int n, int mode) {
  long long &res = dp[n][mode];
  if (~res) return res;

  if (n < 2) return 0;
  else if (n == 2) return mode == 1 or mode == 2;

  if (mode == 0) {
    res = DP(n - 1, 1) * 2ll % MOD;
  } else if (mode == 1) {
    res = (DP(n - 2, 2) + DP(n - 1, 3)) % MOD;
  } else if (mode == 2) {
    res = (DP(n - 2, 2) + DP(n - 1, 1)) % MOD;
  } else {
    res = (DP(n - 2, 3) + DP(n - 2, 1)) % MOD;
  }

  return res;
}

int main() {
  memset(dp, -1, sizeof dp);

  int n;
  cin >> n;

  cout << DP(n, 1);

  return 0;
}