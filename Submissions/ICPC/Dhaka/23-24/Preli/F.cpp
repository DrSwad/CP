#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
  double x, y;
  PT() { x = 0, y = 0; }
  PT(double x, double y) : x(x), y(y) {}
  PT operator -(const PT &a) const { return PT(x - a.x, y - a.y); }
  bool operator <(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
  bool operator ==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
};
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

string to_string(PT p) {
  return to_string(p.x) + ", " + to_string(p.y);
}

vector<PT> upper_convex_hull(vector<PT> &p) {
  if (p.size() <= 1) return p;
  vector<PT> v = p;
  sort(v.begin(), v.end());
  vector<PT> up, dn;
  for (auto&p : v) {
    while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
      up.pop_back();
    }
    up.push_back(p);
  }
  reverse(up.begin(), up.end());
  if (up.size() == 2 && up[0] == up[1]) up.pop_back();
  return up;
}

// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
  double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
  double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
  double det = a1 * b2 - a2 * b1;
  if (det == 0) return 0;
  ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
  return 1;
}

void test_case() {
  int n;
  cin >> n;

  vector<PT> points(n);
  for (auto &p : points) cin >> p.x >> p.y;

  points = upper_convex_hull(points);

  double l_x = points[0].x, r_x = points[0].x;
  for (auto p : points) {
    l_x = min(l_x, p.x);
    r_x = max(r_x, p.y);
  }

  int l_highest = 0, r_highest = (int)points.size() - 1;
  for (int i = 1; i < points.size(); i++) {
    if (points[i].y > points[l_highest].y) {
      l_highest = i;
    }
  }
  for (int i = (int)points.size() - 2; i >= 0; i--) {
    if (points[i].y > points[r_highest].y) {
      r_highest = i;
    }
  }

  const double neg_inf = -1e9, pos_inf = 1e9;

  vector<pair<double, int>> left, right;
  for (int i = 0; i < l_highest; i++) {
    PT inter;
    line_line_intersection(points[i], points[i + 1], PT(0, 0), PT(1, 0), inter);
    left.emplace_back(l_x - inter.x, i);
  }
  for (int i = (int)points.size() - 1; i > r_highest; i--) {
    PT inter;
    line_line_intersection(points[i], points[i - 1], PT(0, 0), PT(1, 0), inter);
    right.emplace_back(inter.x - r_x, i);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(7);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}