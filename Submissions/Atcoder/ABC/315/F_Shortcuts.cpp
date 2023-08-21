#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld INF = 1e18;
const int MAX_MISS = 50;

typedef pair<int, int> point;
#define x first
#define y second

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<point> p(n);
  for (auto & [x, y] : p) cin >> x >> y;

  function<ld(int, int)> dist =
    [&](int i, int j) {
      ld dx = p[i].x - p[j].x;
      ld dy = p[i].y - p[j].y;
      return sqrtl(dx * dx + dy * dy);
    };

  vector dp(n, vector(MAX_MISS, INF));
  dp[0][0] = 0;

  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= max(0, i - MAX_MISS); j--) {
      for (int i_miss = i - j - 1; i_miss < MAX_MISS; i_miss++) {
        int j_miss = i_miss - (i - j - 1);
        dp[i][i_miss] = min(dp[i][i_miss], dp[j][j_miss] + dist(i, j));
      }
    }
  }

  ld ans = INF;
  for (int miss = 0; miss < MAX_MISS; miss++) {
    long long extra = miss == 0 ? 0 : (1ll << (miss - 1));
    ans = min(ans, dp[n - 1][miss] + extra);
  }

  cout << fixed << setprecision(10) << ans << "\n";

  return 0;
}