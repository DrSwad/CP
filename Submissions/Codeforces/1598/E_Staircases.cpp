#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int n, m, q;
int g[N][N];

void reset() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      g[i][j] = 0;
    }
  }
}

int count(int x, int y, pair<int, int> d1, pair<int, int> d2) {
  auto [dx1, dy1] = d1;
  auto [dx2, dy2] = d2;
  int ret = 0;
  for (int xx = x, yy = y; 1 <= xx and xx <= n and 1 <= yy and yy <= m and !g[xx][yy]; ) {
    ret++;
    xx += dx1, yy += dy1;
    if (1 <= xx and xx <= n and 1 <= yy and yy <= m and !g[xx][yy]) ret++;
    else break;
    xx += dx2, yy += dy2;
  }
  return ret;
}

int count(int x, int y) {
  int cnt1 = count(x, y, {1, 0}, {0, 1});
  int cnt2 = count(x, y, {0, 1}, {1, 0});
  // debug(x, y, cnt1, cnt2);
  int cnt3 = count(x, y, {-1, 0}, {0, -1});
  int cnt4 = count(x, y, {0, -1}, {-1, 0});
  // debug(x, y, cnt3, cnt4);
  return cnt1 * cnt4 + cnt2 * cnt3 - 1;
}

void test_case() {
  cin >> n >> m >> q;

  long long ans = 0;
  for (int d = 1; d <= min(n, m); d++) {
    int cnt = 0;
    cnt += n - (d - 1);
    cnt += m - (d - 1);
    cnt--;
    // debug(d, cnt);
    ans += (4ll * d - 2) * cnt;
  }
  ans -= min(n, m);
  // debug(ans);

  while (q--) {
    int x, y;
    cin >> x >> y;
    if (g[x][y] == 0) ans -= count(x, y), g[x][y] = 1;
    else g[x][y] = 0, ans += count(x, y);
    cout << ans << "\n";
  }

  reset();
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