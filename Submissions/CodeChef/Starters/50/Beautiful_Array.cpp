#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MX_MOVE = 15;
const ll INF = 1ll << 60;
const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<ll>> dp(n, vector<ll>(2 * MX_MOVE + 1, INF));
  for (int d = -MX_MOVE; d <= MX_MOVE; d++) {
    int b = a[0] + d;
    if (b < 0) continue;

    int dd = abs(d);
    dp[0][d + MX_MOVE] = 1ll << dd;
  }

  for (int i = 1; i < n; i++) {
    for (int d1 = -MX_MOVE; d1 <= MX_MOVE; d1++) {
      int b1 = a[i - 1] + d1;
      if (b1 < 0) continue;

      for (int d2 = -MX_MOVE; d2 <= MX_MOVE; d2++) {
        int b2 = a[i] + d2;
        if (b2 < 0) continue;

        int dd1 = abs(d1);
        int dd2 = abs(d2);
        if (gcd(b1, b2) == 1) {
          dp[i][d2 + MX_MOVE] = min(dp[i][d2 + MX_MOVE], dp[i - 1][d1 + MX_MOVE] + (1ll << dd2));
          dp[i][d2 + MX_MOVE] = min(dp[i][d2 + MX_MOVE], INF);
        }
      }
    }
  }

  ll ans = *min_element(dp[n - 1].begin(), dp[n - 1].end());
  cout << ans % MOD << "\n";
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