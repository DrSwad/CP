#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const double eps = 1e-6;
inline int dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct point {
  ld x, y;
  point(ld x = 0, ld y = 0) : x(x), y(y) {}
  point operator -(const point &p) const { return point(x - p.x, y - p.y); }
  ld operator *(const point &p) { return x * p.x + y * p.y; }
  ld operator ^(const point &p) { return x * p.y - y * p.x; }
  bool operator <(const point &p) const {return x != p.x ? x < p.x : y < p.y;}
  bool operator ==(const point &p) const {return !dcmp(x - p.x) and !dcmp(y - p.y);}
};

inline double triArea2(point a, point b, point c) { return (b - a) ^ (c - a); }
inline bool inDisk(point a, point b, point p) { return (a - p) * (b - p) <= 0; }
inline bool onSegment(point a, point b, point p) {
  return triArea2(a, b, p) == 0 && inDisk(a, b, p);
}
inline bool segSegIntersection(point a, point b, point c, point d, point &out) {
  if (onSegment(a, b, c)) return out = c, true;
  if (onSegment(a, b, d)) return out = d, true;
  if (onSegment(c, d, a)) return out = a, true;
  if (onSegment(c, d, b)) return out = b, true;

  double oa = triArea2(c, d, a);
  double ob = triArea2(c, d, b);
  double oc = triArea2(a, b, c);
  double od = triArea2(a, b, d);

  if (oa * ob < 0 && oc * od < 0) {
    out = (a * ob - b * oa) / (ob - oa);
    return true;
  }
  return false;
}
inline bool crossesRay(point a, point p, point q) {
  int mul = (q.y >= a.y) - (p.y >= a.y);
  return (mul * triArea2(a, p, q)) > 0;
}
// if strict, returns false when a is on the boundary
inline bool insidePoly(point a, vector<point> poly, bool strict = true) {
  int numCrossings = 0;
  int np = poly.size();
  for (int i = 0; i < np; i++) {
    if (onSegment(poly[i], poly[(i + 1) % np], a)) return !strict;
    numCrossings += crossesRay(a, poly[i], poly[(i + 1) % np]);
  }
  return (numCrossings & 1);   // inside if odd number of crossings
}

ld dist(const point &p1, const point &p2) {
  return hypotl(p1.x - p2.x, p1.y - p2.y);
}

inline bool segPolyIntersection(vector<point> poly, point p, int i) {
  bool intersects = false;
  int np = poly.size();
  for (int j = (i + 1) % np; j != (i - 1 + np) % np; j = (j + 1) % np) {
    point inter;
    if (segSegIntersection(poly[j], poly[(j + 1) % np], p, poly[i], inter)) intersects = true;
  }
  return intersects;
}

ld solve(point from, point to, vector<point> quad) {
  assert(quad.size() == 4);
  if (insidePoly(from, quad) != insidePoly(to, quad)) return -1;
  bool isInside = insidePoly(from, quad);

  bool intersects = false;
  for (int i = 0; i < 4; i++) {
    point inter;
    if (segSegIntersection(quad[i], quad[(i + 1) % 4], from, to, inter)) {
      intersects = true;
      break;
    }
  }
  if (!intersects) return dist(from, to);

  vector<bool> validEdgeFrom(4), validEdgeTo(4);
  for (int i = 0; i < 4; i++) {
    validEdgeFrom[i] = !segPolyIntersection(quad, from, i);
    validEdgeTo[i] = !segPolyIntersection(quad, to, i);
  }

  const ld INF = 1e18;
  ld ans = INF;

  for (int i = 0; i < 4; i++) {
    if (!validEdgeFrom[i]) continue;
    for (int j = 0; j < 4; j++) {
      if (!validEdgeTo[j]) continue;

      ld dist1 = 0, dist2 = 0;
      for (int k = i; k != j % 4; k = (k + 1) % 4) {
        dist1 += dist(quad[k], quad[(k + 1) % 4]);
      }
      for (int k = j; k != i % 4; k = (k + 1) % 4) {
        dist2 += dist(quad[k], quad[(k + 1) % 4]);
      }

      if (i != j and !isInside) {
        // check if edge(i, j) is valid, if it is then it's the best one
        vector<int> restP;
        for (int k = 0; k < 4; k++) {
          if (k != i and k != j) restP.push_back(k);
        }
        assert(restP.size() == 2);
        if ((triArea2(i, j, restP[0]) < 0) == (triArea2(i, j, restP[1]) < 0)) {
          dist1 = dist(quad[i], quad[j]);
        }
      }

      ans = min(ans, dist(from, quad[i]) + min(dist1, dist2) + dist(quad[j], to));
    }
  }

  assert(ans < INF);
  return ans;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int xa, ya, xb, yb;
    scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
    point from(xa, ya);
    point to(xb, yb);

    vector<point> quad;
    for (int i = 0; i < 4; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      quad.emplace_back(x, y);
    }

    ld ans = solve(from, to, quad);
    if (ans < 0) puts("-1");
    else printf("%.10Lf\n", ans);
  }

  return 0;
}