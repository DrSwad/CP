// Expected runtime: O(n)
// Solves Gym 102299J

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef pair <ld, ld> point;

#define x first
#define y second

point operator + (const point &a, const point &b) {
  return point(a.x + b.x, a.y + b.y);
}

point operator - (const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y);
}

point operator * (const point &a, const ld &b) {
  return point(a.x * b, a.y * b);
}

point operator / (const point &a, const ld &b) {
  return point(a.x / b, a.y / b);
}

const ld EPS = 1e-8;
const ld INF = 1e20;
const ld PI = acosl(-1);

inline ld dist (point a, point b) {
  return hypotl(a.x - b.x, a.y - b.y);
}

inline ld sqDist (point a, point b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline ld dot (point a, point b) {
  return a.x * b.x + a.y * b.y;
}

inline ld cross (point a, point b) {
  return a.x * b.y - a.y * b.x;
}

inline ld cross (point a, point b, point c) {
  return cross(b - a, c - a);
}

inline point perp (point a) {
  return point(-a.y, a.x);
}

// circle through 3 points
pair <point, ld> getCircle (point a, point b, point c) {
  pair <point, ld> ret;
  ld den = (ld) 2 * cross(a, b, c);
  ret.x.x = ((c.y - a.y) * (dot(b, b) - dot(a, a)) - (b.y - a.y) * (dot(c, c) - dot(a, a))) / den;
  ret.x.y = ((b.x - a.x) * (dot(c, c) - dot(a, a)) - (c.x - a.x) * (dot(b, b) - dot(a, a))) / den;
  ret.y = dist(ret.x, a);
  return ret;
}

pair <point, ld> minCircleAux (vector <point> &s, point a, point b, int n) {
  ld lo = -INF, hi = INF;
  for (int i = 0; i < n; ++i) {
    auto si = cross(b - a, s[i] - a);
    if (fabs(si) < EPS) continue;
    point m = getCircle(a, b, s[i]).x;
    auto cr = cross(b - a, m - a);
    si < 0 ? hi = min(hi, cr) : lo = max(lo, cr);
  }
  ld v = 0 < lo ? lo : hi < 0 ? hi : 0;
  point c = (a + b) * 0.5 + perp(b - a) * v / sqDist(a, b);
  return {c, sqDist(a, c)};
}

pair <point, ld> minCircle (vector <point> &s, point a, int n) {
  random_shuffle(s.begin(), s.begin() + n);
  point b = s[0], c = (a + b) * 0.5;
  ld r = sqDist(a, c);
  for (int i = 1; i < n; ++i) {
    if (sqDist(s[i], c) > r * (1 + EPS)) {
      tie(c, r) = n == s.size() ? minCircle(s, s[i], i) : minCircleAux(s, a, s[i], i);
    }
  }
  return {c, r};
}

pair <point, ld> minCircle (vector <point> s) {
  assert(!s.empty()); 
  if (s.size() == 1) return {s[0], 0};
  return minCircle(s, s[0], s.size());
}

int n; vector <point> p;

int main() {
  cin >> n;
  while (n--) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    p.emplace_back(x, y);
  }
  pair <point, ld> circ = minCircle(p);
  printf("%0.12f %0.12f %0.12f\n", (double) circ.x.x, (double) circ.x.y, (double) (0.5 * circ.y));
  return 0;
}
