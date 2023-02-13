#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int INV2 = (MOD + 1) / 2;

void test_case() {
    int n, m, k;
    cin >> n >> m >> k;

    vector dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 0;

    for (int nn = 1; nn <= n; nn++) {
        dp[nn][0] = 0;
        dp[nn][nn] = 1ll * k * nn % MOD;

        for (int mm = 1; mm < nn; mm++) {
            dp[nn][mm] = 1ll * (dp[nn - 1][mm - 1] + dp[nn - 1][mm]) * INV2 % MOD;
        }
    }

    cout << dp[n][m] << "\n";
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