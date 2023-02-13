#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  string w;
  cin >> w;

  vector<int> dp(n);
  dp[0] = 0;

  for (int i = 1, prv = w[0] == 'F' ? -1 : 0; i < n; i++) {
    if (w[i] == 'F') {
      dp[i] = dp[i - 1];
    }
    else {
      if (prv == -1 or w[i] == w[prv]) {
        dp[i] = dp[i - 1];
      }
      else {
        dp[i] = dp[i - 1] + (prv + 1);
        if (dp[i] >= MOD) dp[i] -= MOD;
      }

      prv = i;
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += dp[i];
    if (ans >= MOD) ans -= MOD;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}