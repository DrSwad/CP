#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct point {
  ll x, y;
  point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

inline bool up(point p) { return p.y > 0 or (p.y == 0 and p.x >= 0); }
inline long double cross(point p, point q) {
  return p.x * q.y - p.y * q.x;
}
inline long double dist(point p, point q) {
  return hypotl(p.x - q.x, p.y - q.y);
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);

    ll ox, oy;
    scanf("%lld %lld", &ox, &oy);

    int n;
    scanf("%d", &n);

    map<pair<ll, ll>, bool> mp;
    vector<point> v;
    for (int i = 0; i < n; i++) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      x -= ox, y -= oy;

      if (!x and !y) continue;
      if (mp.find({x, y}) != mp.end()) continue;

      mp[{x, y}] = true;
      v.emplace_back(x, y);
    }
    n = v.size();

    sort(v.begin(), v.end(), [](point a, point b) {
      return up(a) == up(b) ? cross(a, b) > 0 : up(a) < up(b);
    });

    v.resize(2 * n);
    copy(v.begin(), v.begin() + n, v.begin() + n);
    // for (int i = 0; i < v.size(); i++)
    //   debug() << name(i) name(v[i].x) name(v[i].y);

    vector<vector<long double>> dp(
        2 * n, vector<long double>(2 * n, -1));
    for (int to = 0; to < 2 * n; to++) {
      for (int from = to - 1; ~from and from >= to - n; from--) {
        if (cross(v[from], v[to]) > 0) {
          dp[to][from] = dist(v[from], v[to]);
        } else {
          for (int mid = from + 1; mid < to; mid++) {
            if (dp[mid][from] != -1 and cross(v[mid], v[to]) > 0) {
              long double curr = dp[mid][from] + dist(v[mid], v[to]);
              dp[to][from] =
                  dp[to][from] == -1 ? curr : min(dp[to][from], curr);
            }
          }
        }
      }
    }

    long double ans = -1;
    for (int i = 0; i < n; i++) {
      if (dp[i + n][i] != -1) {
        ans = ans == -1 ? dp[i + n][i] : min(ans, dp[i + n][i]);
      }
    }

    if (ans == -1) puts("-1");
    else
      printf("%.6Lf\n", ans);
  }

  return 0;
}