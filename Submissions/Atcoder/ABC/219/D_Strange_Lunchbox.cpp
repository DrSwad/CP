#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int n;
int x, y;
int a[N], b[N];
int dp[N][N];

void test_case() {
  cin >> n;
  cin >> x >> y;

  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }

  memset(dp, -1, sizeof dp);
  dp[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int tot = x + y; tot >= 0; tot--) {
      for (int xx = 0; xx <= x and xx <= tot; xx++) {
        int yy = tot - xx;
        if (yy > y) continue;

        int nx = max(0, xx - a[i]);
        int ny = max(0, yy - b[i]);

        int &cval = dp[xx][yy];
        int nval = 1 + dp[nx][ny];

        if (nval) {
          cval = cval == -1 ? nval : min(cval, nval);
        }
      }
    }
  }

  cout << dp[x][y] << "\n";
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