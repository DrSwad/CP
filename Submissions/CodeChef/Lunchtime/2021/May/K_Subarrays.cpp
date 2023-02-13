#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 3;
const int K = 1e2 + 3;
long long NEGINF;

int n, k;
int a[N];
long long dp[N][K][2];

void reset() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      dp[i][j][0] = dp[i][j][1] = NEGINF;
    }
  }
}

void test_case() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      if (dp[i - 1][j][1] > NEGINF) {
        dp[i][j][1] = max(dp[i][j][1], 1ll * a[i] * j + dp[i - 1][j][1]);
      }
      if (dp[i - 1][j - 1][0] > NEGINF) {
        dp[i][j][1] = max(dp[i][j][1], 1ll * a[i] * j + dp[i - 1][j - 1][0]);
      }
      dp[i][j][0] = max(dp[i][j][1], dp[i - 1][j][0]);
    }
  }

  cout << dp[n][k][0] << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  memset(dp, 0b10000000, sizeof dp);
  NEGINF = dp[0][0][0];
  for (int i = 0; i < N; i++) {
    dp[i][0][0] = 0;
  }

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}