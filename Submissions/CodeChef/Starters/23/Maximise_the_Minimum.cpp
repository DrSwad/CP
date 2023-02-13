#include <bits/stdc++.h>
using namespace std;

const int N = 40;
const int SUM = 40 * 40;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  vector dp(2 * SUM, vector(k + 1, -1));
  dp[SUM][0] = 0;

  for (int i = 0; i < n; i++) {
    auto ndp = dp;

    for (int diff = -SUM + 1; diff < SUM; diff++) {
      for (int kk = 1; kk <= k; kk++) {
        int sum1 = dp[diff + SUM][kk - 1];
        int sum2 = dp[diff + SUM][kk - 1];
        if (diff < 0) sum2 += -diff;
        else sum1 += diff;
        if (sum1 < 0 or sum2 < 0) continue;

        sum1 += a[i], sum2 += b[i];
        if (sum1 >= SUM or sum2 >= SUM) continue;
        int ndiff = sum1 - sum2;
        ndp[ndiff + SUM][kk] = max(ndp[ndiff + SUM][kk], min(sum1, sum2));
      }
    }

    swap(dp, ndp);
  }

  int ans = 0;
  for (int diff = -SUM + 1; diff < SUM; diff++) {
    ans = max(ans, dp[diff + SUM][k]);
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}