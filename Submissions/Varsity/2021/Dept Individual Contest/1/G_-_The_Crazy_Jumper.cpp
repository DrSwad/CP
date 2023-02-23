#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  unordered_map<int, int> last_at;
  vector<int> dp(n);

  last_at[c[n - 1]] = n - 1;
  dp[n - 1] = 0;

  for (int i = n - 2; i >= 0; i--) {
    dp[i] = 1 + dp[i + 1];
    if (last_at.find(c[i]) != last_at.end()) {
      dp[i] = min(dp[i], 1 + dp[last_at[c[i]]]);
    }
    last_at[c[i]] = i;
  }

  cout << dp[0] << "\n";
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