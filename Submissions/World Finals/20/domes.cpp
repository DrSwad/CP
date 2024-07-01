#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-9;

typedef long double T; // or long long
typedef complex<T> point;
#define x real()
#define y imag()
typedef pair<point, T> line;
typedef line halfplane;

T dot(point a, point b) {
  return (conj(a) * b).x;
}

T cross(point v, point w) {
  return (conj(v) * w).y;
}

T sq(point p) { return dot(p, p); }

T side(line l, point p) {
  auto [v, c] = l;
  return cross(v, p) - c;
}

line get_line(point p1, point p2) {
  point v = p2 - p1;
  return {v, cross(v, p1)};
}

// Check if point 'r' is outside this half-plane.
// Every half-plane allows the region to the LEFT of its line.
bool out(halfplane hp, point r) {
  return side(hp, r) < -eps;
}

bool inter(line l1, line l2, point &out) {
  auto [v1, c1] = l1;
  auto [v2, c2] = l2;
  T d = cross(v1, v2);
  if (d == 0) return false;
  out = (v2 * c1 - v1 * c2) / d; // requires floating-point coordinates
  return true;
}

point inter(line l1, line l2) {
  point out;
  assert(inter(l1, l2, out));
  return out;
}

bool upper_half(point p) { // true if in upper half
  assert(p.x != 0 || p.y != 0); // the argument of (0, 0) is undefined
  return p.y > 0 || (p.y == 0 && p.x < 0);
}

bool polar_compare(point p1, point p2) {
  return
    make_tuple(upper_half(p1), 0, sq(p1))
    < make_tuple(upper_half(p2), cross(p1, p2), sq(p2));
}

// Actual algorithm
vector<point> hp_intersect(
  const vector<halfplane> &hps,
  const long double dx,
  const long double dy
) {
  vector<halfplane> _hps = hps;

  point box[4] = {  // Bounding box in CCW order
    point(dx, dy),
    point(0, dy),
    point(0, 0),
    point(dx, 0)
  };

  for (int i = 0; i < 4; i++) { // Add bounding box half-planes.
    halfplane aux = get_line(box[i], box[(i + 1) % 4]);
    _hps.push_back(aux);
  }

  // Sort by angle and start algorithm
  sort(
    _hps.begin(),
    _hps.end(),
    [](halfplane hp1, halfplane hp2) {
      point v1 = hp1.first, v2 = hp2.first;
      return polar_compare(v1, v2);
    }
  );

  deque<halfplane> dq;
  int len = 0;
  for (int i = 0; i < int(_hps.size()); i++) {
    // Remove from the back of the deque while last half-plane is redundant
    while (len > 1 && out(_hps[i], inter(dq[len - 1], dq[len - 2]))) {
      dq.pop_back();
      --len;
    }

    // Remove from the front of the deque while first half-plane is redundant
    while (len > 1 && out(_hps[i], inter(dq[0], dq[1]))) {
      dq.pop_front();
      --len;
    }

    // Special case check: Parallel half-planes
    if (len > 0 && fabsl(cross(_hps[i].first, dq[len - 1].first)) < eps) {
      // Opposite parallel half-planes that ended up checked against each other.
      if (dot(_hps[i].first, dq[len - 1].first) < 0.0) return vector<point>();

      // Same direction half-plane: keep only the leftmost half-plane.
      auto [vi, ci] = _hps[i];
      auto [v, c] = dq[len - 1];
      if (ci * abs(v) > c * abs(vi)) {
        dq.pop_back();
        --len;
      }
      else continue;
    }

    // Add new half-plane
    dq.push_back(_hps[i]);
    ++len;
  }

  // Final cleanup: Check half-planes at the front against the back and vice-versa
  while (len > 2 && out(dq[0], inter(dq[len - 1], dq[len - 2]))) {
    dq.pop_back();
    --len;
  }

  while (len > 2 && out(dq[len - 1], inter(dq[0], dq[1]))) {
    dq.pop_front();
    --len;
  }

  // Report empty intersection if necessary
  if (len < 3) return vector<point>();

  // Reconstruct the convex polygon from the remaining half-planes.
  vector<point> ret(len);
  for (int i = 0; i + 1 < len; i++) {
    ret[i] = inter(dq[i], dq[i + 1]);
  }
  ret.back() = inter(dq[len - 1], dq[0]);
  return ret;
}

inline T area(point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<point> convex_hull(vector<point> p) {
  int n = p.size(), m = 0;
  if (n < 3) return p;
  vector<point> hull(n + n);
  sort(p.begin(), p.end(), polar_compare);
  for (int i = 0; i < n; ++i) {
    while (m > 1 and area(hull[m - 2], hull[m - 1], p[i]) <= 0) --m;
    hull[m++] = p[i];
  }
  for (int i = n - 2, j = m + 1; i >= 0; --i) {
    while (m >= j and area(hull[m - 2], hull[m - 1], p[i]) <=
           0
    ) --m;
    hull[m++] = p[i];
  } hull.resize(m - 1); return hull;
}

long double area(vector<point> p) {
  long double area = 0.0;
  for (int i = 0, n = p.size(); i < n; i++) {
    area += cross(p[i], p[(i + 1) % n]);
  }
  return abs(area) / 2.0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  double dx, dy;
  int n;
  cin >> dx >> dy >> n;

  vector<point> p(n);
  for (int i = 0; i < n; i++) {
    T _x, _y;
    cin >> _x >> _y;
    p[i] = {_x, _y};
  }

  vector<int> order(n);
  for (int &i : order) cin >> i, i--;

  vector<halfplane> hps;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      hps.push_back(get_line(p[order[j]], p[order[i]]));
    }
  }

  vector<point> hps_inter = hp_intersect(hps, dx, dy);

  long double hps_area = area(hps_inter);

  long double hps_ch_area = 0;

  vector<point> ch = convex_hull(p);

  if (ch.size() > 1) {
    for (int i = 0; i < ch.size(); i++) {
      hps.push_back(get_line(ch[i], ch[(i + 1) % n]));
    }

    vector<point> hps_ch_inter = hp_intersect(hps, dx, dy);

    hps_ch_area = area(hps_ch_inter);
  }

  cout << fixed << setprecision(6)
       << max(0.0l, hps_area - hps_ch_area)
       << "\n";

  return 0;
}