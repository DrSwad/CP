#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;

#define x first
#define y second

inline ll area(point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<point> convexHull(vector<point> p) {
  int n = p.size(), m = 0;
  if (n < 3) return p;
  vector<point> hull(n + n);
  sort(p.begin(), p.end());
  for (int i = 0; i < n; ++i) {
    while (m > 1 and area(hull[m - 2], hull[m - 1], p[i]) <= 0) --m;
    hull[m++] = p[i];
  }
  for (int i = n - 2, j = m + 1; i >= 0; --i) {
    while (m >= j and area(hull[m - 2], hull[m - 1], p[i]) <= 0) --m;
    hull[m++] = p[i];
  }
  hull.resize(m - 1); return hull;
}

// points of the polygon has to be in ccw order
// if strict, returns false when point is on the boundary of hull
inline bool onSegment(point a, point b, point p) { return area(a, b, p) == 0 and (a.x == p.x or b.x == p.x or (a.x < p.x) != (b.x < p.x)); }
inline bool insideConvexPoly(vector<point> &hull, point p, bool strict) {
  int n = hull.size();
  int st = 1, en = n - 1, mid;
  while (en - st > 1) {
    mid = (st + en) >> 1;
    if (area(hull[0], hull[mid], p) < 0) en = mid;
    else st = mid;
  }
  if (strict) {
    if (st == 1) if (onSegment(hull[0], hull[st], p)) return false;
    if (en == n - 1) if (onSegment(hull[0], hull[en], p)) return false;
    if (onSegment(hull[st], hull[en], p)) return false;
  }
  if (area(hull[0], hull[st], p) < 0) return false;
  if (area(hull[st], hull[en], p) < 0) return false;
  if (area(hull[en], hull[0], p) < 0) return false;
  return true;
}

ll seed1, seed2;
int get_random() {
  seed1 = (seed1 * 1103515243 + 12345) % (2012345671);
  seed2 = (seed2 * 1092104927 + 54321) % (2094828103);
  int r = (seed1 * seed2) % 100000;
  return r;
}

int main() {
  int t, cs;
  scanf("%d", &t);

  for (cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d %lld %lld", &n, &seed1, &seed2);

    vector<point> points;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      int x = get_random();
      int y = get_random();
      point np{x, y};
      if (i <= 2) {
        points.emplace_back(np);
        continue;
      }
      if (i == 3 or !insideConvexPoly(points, np, false)) {
        points.emplace_back(np);
        points = convexHull(points);
      }
      ll A = 0;
      int H = points.size();
      for (int i = 1; i < H - 1; i++) {
        int j = (i + 1) % H;
        A += area(points[0], points[i], points[j]);
      }
      ans += abs(A);
    }

    printf("Case %d: %lld\n", cs, ans);
  }

  return 0;
}