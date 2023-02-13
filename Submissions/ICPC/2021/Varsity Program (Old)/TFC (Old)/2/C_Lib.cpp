#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define x first
#define y second

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const int RANDOM = (long long)(make_unique<char>().get())
                     ^ chrono::high_resolution_clock::now()
                     .time_since_epoch()
                     .count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  int operator()(unsigned long long x) const { return hash_f(x) ^ RANDOM; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<pair<int, int>> points(n);
  for (auto & [x, y] : points) cin >> x >> y;

  auto normalize_slope = [&](int sx, int sy) {
    // debug(sx, sy);
    if (sx < 0) sx = -sx, sy = -sy;
    if (sx == 0) sy = 1;
    if (sy == 0) sx = 1;

    ull _sx = (ull)sx << 32;
    ull _sy = (sy >= 0 ? sy : (1ull << 32) + (ull)sy);
    ull s = _sx + _sy;
    // debug(s);
    return s;
  };

  auto retrieve_slope = [&](ull s) {
    // debug(s);
    int sx = s >> 32;
    ull _sy = s & ((1ull << 32) - 1);
    int sy = _sy;
    // debug(sx, sy);
    return make_pair(sx, sy);
  };

  auto get_slope = [&](int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = gcd(abs(dx), abs(dy));
    dx /= d;
    dy /= d;
    return normalize_slope(dx, dy);
  };

  vector<gp_hash_table<ull, int, chash>> slopes_from_point(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        // debug(i, j);
        slopes_from_point[i][get_slope(points[i].x, points[i].y, points[j].x, points[j].y)]++;
      }
    }
  }

  // debug(slopes_from_point);

  while (q--) {
    int qx, qy;
    cin >> qx >> qy;

    gp_hash_table<ull, int, chash> slopes_from_query;
    for (int i = 0; i < n; i++) {
      slopes_from_query[get_slope(qx, qy, points[i].x, points[i].y)]++;
    }

    // debug(slopes_from_query);

    long long ans_at_center = 0, ans_at_corner = 0;

    for (int i = 0; i < n; i++) {
      auto s = get_slope(qx, qy, points[i].x, points[i].y);
      auto [sx, sy] = retrieve_slope(s);
      swap(sx, sy);
      sx = -sx;
      s = normalize_slope(sx, sy);

      ans_at_center += slopes_from_query[s];
      ans_at_corner += slopes_from_point[i][s];
    }

    cout << ans_at_center / 2 + ans_at_corner << "\n";
  }

  return 0;
}