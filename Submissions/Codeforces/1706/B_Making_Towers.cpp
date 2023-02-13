#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<vector<int>> dp(n, vector<int>(2, 0));
  for (int i = 0; i < n; i++) {
    int j1 = i & 1, j2 = (i & 1) ^ 1;
    dp[a[i]][j1] = max(dp[a[i]][j1], 1 + dp[a[i]][j2]);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << max(dp[i][0], dp[i][1]);
  }
  cout << "\n";
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