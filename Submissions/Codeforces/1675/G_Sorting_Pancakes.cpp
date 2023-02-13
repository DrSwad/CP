#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<vector<int>>> dp(n + 1, vector(m + 1, vector(m + 1, -1)));
  for (int a0 = 0; a0 <= m; a0++) dp[0][a0][0] = 0;

  int psum = 0;
  for (int i = 1; i <= n; psum += a[i - 1], i++) {
    for (int ai = m; ai >= 0; ai--) {
      for (int sum = ai; sum <= m; sum++) {
        int &ans = dp[i][ai][sum];
        {
          int curr = dp[i - 1][ai][sum - ai];
          if (~curr) {
            curr += abs(psum - (sum - ai));
            ans = ans == -1 ? curr : min(curr, ans);
          }
        }
        if (ai + 1 <= m and sum + 1 <= m) {
          int curr = dp[i][ai + 1][sum + 1];
          if (~curr) ans = ans == -1 ? curr : min(curr, ans);
        }
        if (ai + 1 <= m) {
          int curr = dp[i][ai + 1][sum];
          if (~curr) ans = ans == -1 ? curr : min(ans, curr);
        }
      }
    }
  }

  assert(psum == m);

  int ans = -1;
  for (int an = 0; an <= m; an++) {
    int curr = dp[n][an][psum];
    if (~curr) ans = ans == -1 ? curr : min(ans, curr);
  }
  cout << ans << "\n";

  return 0;
}