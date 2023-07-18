#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> point;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
#define x first
#define y second

int sign(double x) { return (x > eps) - (x < -eps); }
inline double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
point operator+(point a, point b) { return {a.x + b.x, a.y + b.y}; }
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator*(point a, double r) { return {a.x * r, a.y * r}; }
inline double dist2(point a, point b) { return dot(a - b, a - b); }
inline double dist(point a, point b) { return sqrt(dot(a - b, a - b)); }
point project_from_point_to_seg(point a, point b, point c) {
  double r = dist2(a, b);
  if (sign(r) == 0) return a;
  r = dot(c - a, b - a) / r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b - a) * r;
}
// minimum distance from point c to segment ab
double dist_from_point_to_seg(point a, point b, point c) {
  return dist(c, project_from_point_to_seg(a, b, c));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  point c;
  cin >> n >> c.x >> c.y;

  vector<point> p(n);
  for (auto & [x, y] : p) cin >> x >> y;

  double max_dist = 0;
  double min_dist = HUGE_VAL;

  for (int i = 0; i < n; i++) {
    max_dist = max(max_dist, dist(p[i], c));
    min_dist = min(min_dist, dist_from_point_to_seg(p[i], p[(i + 1) % n], c));
  }

  cout << fixed << setprecision(18) << PI * (max_dist * max_dist - min_dist * min_dist) << "\n";

  return 0;
}