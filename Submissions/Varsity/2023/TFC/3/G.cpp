#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, x, y, a, b;
  cin >> n >> m >> x >> y >> a >> b;

  int g = gcd(a, b);
  a /= g;
  b /= g;

  {
    int L = 1, R = int(1e9) + 1;
    while (R - L > 1) {
      int mid = (L + R) / 2;
      long long cur_x = 1ll * a * mid;
      long long cur_y = 1ll * b * mid;
      if (cur_x > n or cur_y > m) R = mid;
      else L = mid;
    }
    a *= L;
    b *= L;
  }

  int mn_x0 = 0, mx_x0 = n - a;
  int mn_y0 = 0, mx_y0 = m - b;

  int mid_x0 = max(mn_x0, min(mx_x0, x - a / 2));
  int mid_y0 = max(mn_y0, min(mx_y0, y - b / 2));

  vector<pair<int, int>> candidates;
  for (int dx = -10; dx <= 10; dx++) {
    for (int dy = -10; dy <= 10; dy++) {
      int cur_x0 = mid_x0 + dx;
      int cur_y0 = mid_y0 + dy;
      if (mn_x0 <= cur_x0 and cur_x0 <= mx_x0 and
          mn_y0 <= cur_y0 and cur_y0 <= mx_y0 and
          cur_x0 <= x and x <= cur_x0 + a and
          cur_y0 <= y and y <= cur_y0 + b
      ) {
        candidates.emplace_back(cur_x0, cur_y0);
      }
    }
  }

  typedef pair<int, int> point;
  function<bool(point, point)> compare =
    [&](const point&p1, const point&p2) {
      auto [x1, y1] = p1;
      auto [x2, y2] = p2;
      int cx1 = x1 + (x1 + a);
      int cy1 = y1 + (y1 + b);
      int cx2 = x2 + (x2 + a);
      int cy2 = y2 + (y2 + b);
      int xx = x + x;
      int yy = y + y;
      long long dist1 = 1ll * (cx1 - xx) * (cx1 - xx) + 1ll * (cy1 - yy) * (cy1 - yy);
      long long dist2 = 1ll * (cx2 - xx) * (cx2 - xx) + 1ll * (cy2 - yy) * (cy2 - yy);
      if (dist1 != dist2) return dist1 < dist2;
      tuple<int, int, int, int> tup1 = {x1, y1, x1 + a, y1 + b};
      tuple<int, int, int, int> tup2 = {x2, y2, x2 + a, y2 + b};
      return tup1 < tup2;
    };

  sort(candidates.begin(), candidates.end(), compare);

  int x0 = candidates[0].first;
  int y0 = candidates[0].second;
  cout << x0 << " " << y0 << " " << x0 + a << " " << y0 + b << "\n";

  return 0;
}