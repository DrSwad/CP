#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;

inline int dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  void read() { scanf("%lf%lf", &x, &y); }
  void write() { printf("%lf %lf", x, y); }

  bool operator ==(const Point&u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
  bool operator !=(const Point&u) const { return !(*this == u); }
  bool operator <(const Point&u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }
  bool operator >(const Point&u) const { return u < *this; }
  bool operator <=(const Point&u) const { return *this < u || *this == u; }
  bool operator >=(const Point&u) const { return *this > u || *this == u; }
  Point operator +(const Point&u) { return Point(x + u.x, y + u.y); }
  Point operator -(const Point&u) { return Point(x - u.x, y - u.y); }
  Point operator *(const double u) { return Point(x * u, y * u); }
  Point operator /(const double u) { return Point(x / u, y / u); }
  double operator *(const Point&u) { return x * u.y - y * u.x; }
};
typedef Point Vector;
typedef vector<Point> Polygon;

double getCross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

bool getIntersection(Point p, Vector v, Point q, Vector w, Point&o) {
  if (dcmp(getCross(v, w)) == 0) return false;
  Vector u = p - q;
  double k = getCross(w, u) / getCross(v, w);
  o = p + v * k;
  return true;
}

struct DirLine {
  Point p;
  Vector v;
  double ang;
  DirLine() {}
  DirLine(Point p, Vector v) : p(p), v(v) { ang = atan2(v.y, v.x); }
  bool operator <(const DirLine&u) const { return ang < u.ang; }
};

bool onLeft(DirLine l, Point p) { return dcmp(l.v * (p - l.p)) >= 0; }

int halfPlaneIntersection(DirLine* li, int n, Point* poly) {
  sort(li, li + n);

  int first, last;
  Point* p = new Point[n];
  DirLine* q = new DirLine[n];
  q[first = last = 0] = li[0];

  for (int i = 1; i < n; i++) {
    while (first < last && !onLeft(li[i], p[last - 1])) last--;
    while (first < last && !onLeft(li[i], p[first])) first++;
    q[++last] = li[i];

    if (dcmp(q[last].v * q[last - 1].v) == 0) {
      last--;
      if (onLeft(q[last], li[i].p)) q[last] = li[i];
    }

    if (first < last) getIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
  }

  while (first < last && !onLeft(q[first], p[last - 1])) last--;
  if (last - first <= 1) { delete[] p; delete[] q; return 0; }
  getIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);

  int m = 0;
  for (int i = first; i <= last; i++) poly[m++] = p[i];
  delete[] p; delete[] q;
  return m;
}

double getSignedArea(Point* p, int n) {
  double ret = 0;
  for (int i = 0; i < n - 1; i++) ret += (p[i] - p[0]) * (p[i + 1] - p[0]);
  return ret / 2;
}

const int N = 35;
DirLine dl[N * N];
int dsz = 0;
Point poly[N * N];

int main() {
  int n;
  scanf("%d", &n);

  while (n--) {
    int psz;
    scanf("%d", &psz);

    Polygon poly;
    for (int i = 0; i < psz; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      poly.emplace_back(x, y);
    }

    for (int i = 0; i < psz; i++) {
      int j = i + 1;
      if (j == psz) j = 0;
      dl[dsz++] = DirLine(poly[i], poly[j] - poly[i]);
    }
  }

  int psz = halfPlaneIntersection(dl, dsz, poly);
  printf("%.6lf\n", fabs(getSignedArea(poly, psz)));

  return 0;
}