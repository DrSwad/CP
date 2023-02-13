#include <bits/stdc++.h>
using namespace std;

const int N = 405;

int n, m;
string g[N];
int dp[N][N];

int rect(int x1, int y1, int x2, int y2) {
  return dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
}

int black(int x1, int y1, int x2, int y2) {
  return rect(x1, y1, x2, y2);
}

int white(int x1, int y1, int x2, int y2) {
  return (x2 - x1 + 1) * (y2 - y1 + 1) - rect(x1, y1, x2, y2);
}

void test_case() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> g[i], g[i] = ' ' + g[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = (g[i][j] - '0') + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
  }

  int ans = n * m;

  for (int i = 1; i <= n; i++) {
    for (int j = i + 4; j <= n; j++) {
      int mx = - n * m;
      for (int k = 4; k <= m; k++) {
        mx = max(mx,
          black(i + 1, 1, j - 1, k - 3) +
          white(i, 1, i, k - 3) +
          white(j, 1, j, k - 3) -
          white(i + 1, k - 3, j - 1, k - 3)
        );

        int curr = 0;
        curr += black(i + 1, 1, j - 1, k - 1);
        curr += white(i, 1, i, k - 1);
        curr += white(j, 1, j, k - 1);
        curr += white(i + 1, k, j - 1, k);
        curr -= mx;
        ans = min(ans, curr);
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}