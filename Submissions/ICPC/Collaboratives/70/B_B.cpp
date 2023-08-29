#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos(-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
  double x, y;
  PT() { x = 0, y = 0; }
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator +(const PT &a) const { return PT(x + a.x, y + a.y); }
  PT operator -(const PT &a) const { return PT(x - a.x, y - a.y); }
  PT operator *(const double a) const { return PT(x * a, y * a); }
  friend PT operator *(const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
  PT operator /(const double a) const { return PT(x / a, y / a); }
  bool operator ==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
  bool operator !=(PT a) const { return !(*this == a); }
  bool operator <(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
  bool operator >(PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
  double norm() { return sqrt(x * x + y * y); }
  double norm2() { return x * x + y * y; }
  PT perp() { return PT(-y, x); }
  double arg() { return atan2(y, x); }
  PT truncate(double r) {   // returns a vector with norm r and having same direction
    double k = norm();
    if (!sign(k)) return *this;
    r /= k;
    return PT(x * r, y * r);
  }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

vector<PT> convex_hull(vector<PT> &p) {
  if (p.size() <= 1) return p;
  vector<PT> v = p;
  sort(v.begin(), v.end());
  vector<PT> up, dn;
  for (auto&p : v) {
    while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
      up.pop_back();
    }
    while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
      dn.pop_back();
    }
    up.push_back(p);
    dn.push_back(p);
  }
  v = dn;
  if (v.size() > 1) v.pop_back();
  reverse(up.begin(), up.end());
  up.pop_back();
  for (auto&p : up) {
    v.push_back(p);
  }
  if (v.size() == 2 && v[0] == v[1]) v.pop_back();
  return v;
}

// minimum distance from point c to line through a and b
double dist_from_point_to_line(PT a, PT b, PT c) {
  return fabs(cross(b - a, c - a) / (b - a).norm());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, r;
  cin >> n >> r;

  vector<PT> poly;
  for (int i = 0; i < n; i++) {
    double x, y;
    cin >> x >> y;
    poly.emplace_back(x, y);
  }

  poly = convex_hull(poly);
  n = poly.size();
  double ans = HUGE_VAL;

  for (int st = 0, at = 1 % n; st < n; st++) {
    int en = (st + 1) % n;
    while (true) {
      int nxt = (at + 1) % n;
      if (nxt == st) break;
      if (dist_from_point_to_line(poly[st], poly[en], poly[nxt]) > dist_from_point_to_line(poly[st], poly[en], poly[at])) {
        at = nxt;
      }
      else break;
    }
    ans = min(ans, dist_from_point_to_line(poly[st], poly[en], poly[at]));
  }

  cout << fixed << setprecision(10) << ans << "\n";

  return 0;
}