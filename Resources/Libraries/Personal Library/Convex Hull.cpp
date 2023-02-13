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

int main() {
  int n; cin >> n;
  vector<point> p(n);
  for (auto &it : p) scanf("%lld %lld", &it.x, &it.y);
  vector<point> hull = convexHull(p);
  for (auto it : hull) printf("%lld %lld\n", it.x, it.y);
  return 0;
}