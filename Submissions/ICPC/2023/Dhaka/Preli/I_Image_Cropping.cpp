#include <bits/stdc++.h>
using namespace std;

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

// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<PT> &p, const PT&x) {  // O(log n)
  int n = p.size(); assert(n >= 3);
  int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
  if (a < 0 || b > 0) return 1;
  int l = 1, r = n - 1;
  while (l + 1 < r) {
    int mid = l + r >> 1;
    if (orientation(p[0], p[mid], x) >= 0) l = mid;
    else r = mid;
  }
  int k = orientation(p[l], p[r], x);
  if (k <= 0) return -k;
  if (l == 1 && a == 0) return 0;
  if (r == n - 1 && b == 0) return 0;
  return -1;
}

typedef long long ll;
const int MX = 1e8;

void test_case() {
  vector<PT> poly(4);
  for (PT&p : poly) cin >> p.x >> p.y;
  poly = convex_hull(poly);

  PT pivot;
  cin >> pivot.x >> pivot.y;

  int w, h;
  cin >> w >> h;
  if (w % 2 == 1 or h % 2 == 1) w *= 2, h *= 2;

  int L = 0, R = 1e9;
  while (R > L + 1) {
    int mid = (L + R) / 2;
    ll W = (ll)w * mid;
    ll H = (ll)h * mid;
    ll x[2], y[2];
    x[0] = (ll)pivot.x - W / 2;
    x[1] = (ll)pivot.x + W / 2;
    y[0] = (ll)pivot.y - H / 2;
    y[1] = (ll)pivot.y + H / 2;
    bool possible = true;
    if (x[0] < -MX or x[1] > MX or y[0] < -MX or y[1] > MX) possible = false;
    else {
      for (int xi = 0; xi < 2 and possible; xi++) {
        for (int yi = 0; yi < 2 and possible; yi++) {
          PT p((int)x[xi], (int)y[yi]);
          if (is_point_in_convex(poly, p) == 1) possible = false;
        }
      }
    }

    if (possible) L = mid;
    else R = mid;
  }

  int W = w * L, H = h * L;
  cout << (ll)W * H << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}