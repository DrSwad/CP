#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<map<int, bool>> dp(n);
  dp[0][a[0]] = dp[0][a[0] - 1] = dp[0][a[0] + 1] = true;

  for (int i = 1; i < n; i++) {
    if (dp[i - 1].find(a[i] - 2) != dp[i - 1].end()) dp[i][a[i] - 1] = true;
    if (dp[i - 1].find(a[i] - 1) != dp[i - 1].end()) dp[i][a[i]] = true;
    if (dp[i - 1].find(a[i]) != dp[i - 1].end()) dp[i][a[i] + 1] = true;
  }

  cout << (dp[n - 1].size() > 0 ? "YES" : "NO") << "\n";
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