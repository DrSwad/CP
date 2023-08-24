#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> s(n);
  for (int &i : s) cin >> i, i--;

  vector dp(m + 1, vector(m + 1, 0));
  for (int d2 = 0; d2 <= m; d2++) {
    for (int d1 = 0; d1 <= m; d1++) {
      if (d1 == 0) dp[d1][d2] = 0;
      else if (d2 == 0) dp[d1][d2] = d1;
      else {
        dp[d1][d2] = add(dp[d1][d2], mul(inv2, add(1, dp[d1 - 1][d2])));
        if (d1 + 1 <= m) {
          dp[d1][d2] = add(dp[d1][d2], mul(inv2, dp[d1 + 1][d2 - 1]));
        }
      }
    }
  }

  int ans = m - s[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    int d1 = s[i + 1] - s[i];
    int d2 = m - s[i + 1];
    ans = add(ans, dp[d1][d2]);
  }

  cout << ans << "\n";

  return 0;
}