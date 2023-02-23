#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const double eps = 1e-10L;

struct Point {
  ld x, y;
  Point() {}
  Point(ld x, ld y) : x(x), y(y) {}
  Point operator-(Point &p) {
    return Point(x - p.x, y - p.y);
  }
  ld cross(Point p) {
    return x * p.y - y * p.x;
  }
  ld abs() {
    return sqrtl(x * x + y * y);
  }
};
ostream& operator<<(ostream&os, const Point &p) {
  return os << "(" << p.x << ", " << p.y << ")";
}
ostream& operator<<(ostream&os, const vector<Point> &poly) {
  os << "[";
  for (int i = 0; i < poly.size(); i++) {
    if (i) os << " ";
    os << poly[i];
  }
  cerr << "]";
  return os;
}

void normalizePolygon(vector<Point> &poly) {
  sort(
    poly.begin() + 1,
    poly.end(),
    [&](Point &p1, Point &p2) {
    return (p1 - poly[0]).cross(p2 - poly[0]) > 0;
  }
    );
}

Point rotatePoint(Point p, Point u) {
  ld a = p.x;
  ld b = p.y;
  ld c = u.x;
  ld d = u.y;
  return Point(a * c - b * d, a * d + b * c);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int tolerate;
  cin >> tolerate;

  vector<Point> car(4);
  for (int i = 0; i < 4; i++) {
    cin >> car[i].x >> car[i].y;
  }

  int potholes;
  cin >> potholes;

  vector<vector<Point>> polygons(potholes);

  for (int i = 0; i < potholes; i++) {
    int sz;
    cin >> sz;

    while (sz--) {
      ld x, y, z;
      cin >> x >> y >> z;

      if (fabs(z) < eps) {
        polygons[i].push_back(Point(x, y));
      }
    }

    normalizePolygon(polygons[i]);
  }

  /*
     for (auto poly : polygons) {
     cerr << endl << poly << endl;
     }
   */

  Point o, u;
  {
    ld ox = ((car[0].x + car[1].x) / 2 + (car[2].x + car[3].x) / 2) / 2;
    ld oy = ((car[0].y + car[1].y) / 2 + (car[2].y + car[3].y) / 2) / 2;
    o = Point(ox, oy);
    u = Point((car[0].x + car[1].x) / 2, (car[0].y + car[1].y) / 2);
    u = u - o;
    ld len = u.abs();
    u.x /= len, u.y /= len;
    u.y = -u.y;
  }

  for (auto &p : car) {
    p = rotatePoint(p - o, u);
  }

  for (auto &poly : polygons) {
    for (auto &p: poly) {
      p = rotatePoint(p - o, u);
    }
  }

  // cerr << car << endl;
  // for (auto &poly : polygons) cerr << poly << endl;

  ld down_y = car[0].y, up_y = car[1].y;
  ld left_x = car[2].x, right_x = car[0].x;

  vector<ld> mn_xs;
  for (auto poly : polygons) {
    {
      ld mx_y = poly[0].y, mn_y = poly[0].y;
      for (int i = 1; i < poly.size(); i++) {
        mx_y = max(mx_y, poly[i].y);
        mn_y = min(mn_y, poly[i].y);
      }
      if (mn_y >= up_y or mx_y <= down_y) continue;
    }

    vector<ld> valid_x;

    for (auto p : poly) {
      if (down_y <= p.y and p.y <= up_y) {
        valid_x.push_back(p.x);
      }
    }

    vector<ld> Ys(2);
    Ys[0] = down_y, Ys[1] = up_y;

    for (auto Y : Ys) {
      int sz = poly.size();
      for (int i = 0; i < sz; i++) {
        int j = (i + 1) % sz;
        if (poly[i].y != Y and poly[j].y != Y) {
          if ((poly[i].y > Y) != (poly[j].y > Y)) {
            ld x1 = poly[i].x, y1 = poly[i].y;
            ld x2 = poly[j].x, y2 = poly[j].y;
            ld dx = x2 - x1, dy = y2 - y1;
            ld dy2 = Y - y1;
            ld dx2 = x1 + dx / dy * dy2;
            valid_x.push_back(x2 + dx2);
          }
        }
      }
    }

    if (!valid_x.empty()) {
      ld mn_x = *min_element(valid_x.begin(), valid_x.end());
      ld mx_x = *max_element(valid_x.begin(), valid_x.end());
      if ((left_x <= mn_x and mn_x <= right_x) or
          (left_x <= mx_x and mx_x <= right_x) or
          (mn_x < left_x and right_x < mx_x)
          ) {
        tolerate--;
      }
      else mn_xs.push_back(mn_x);
    }
  }

  ld ans = 0;
  sort(mn_xs.begin(), mn_xs.end());
  for (ld x : mn_xs) {
    if (x > right_x and tolerate >= 0) {
      tolerate--;
      if (tolerate < 0) {
        ans = x - right_x;
        break;
      }
    }
  }

  if (tolerate >= 0) cout << "oo\n";
  else cout << fixed << setprecision(8) << ans << "\n";

  return 0;
}