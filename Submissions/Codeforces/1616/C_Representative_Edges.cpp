#include <bits/stdc++.h>
using namespace std;

const int N = 75;
const int A = 405;

int a[N];
int dp[N][N][2 * A + 1];

void test_case() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int d1 = 1; d1 < n; d1++) {
    for (int d2 = -A; d2 <= A; d2++) {
      dp[0][d1][d2 + A] = 1;
    }
  }

  int ans = 1;

  for (int i = 1; i < n; i++) {
    for (int d1 = 1; d1 < n; d1++) {
      for (int d2 = -A; d2 <= A; d2++) {
        dp[i][d1][d2 + A] = (i - d1 < 0 or a[i - d1] != a[i] + d2) ? 1 : 1 + dp[i - d1][d1][d2 + A];
        ans = max(ans, dp[i][d1][d2 + A]);
      }
    }
  }

  cout << n - ans << "\n";

  memset(dp, 0, sizeof dp);
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