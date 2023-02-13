#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

void test_case() {
  int k;
  cin >> k;

  vector<ll> dp(k);
  dp[0] = 1;

  for (int i = 1; i < k; i++) {
    dp[i] = 4ll * dp[i - 1] % MOD;
    dp[i] = dp[i] * dp[i] % MOD;
  }

  cout << 6ll * dp.back() % MOD << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}