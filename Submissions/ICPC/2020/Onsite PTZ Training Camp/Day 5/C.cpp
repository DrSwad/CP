#include <bits/stdc++.h>
using namespace std;

typedef int T;
typedef long long TT;
typedef long double ld;
const ld PI = acos(-1.0L);

struct Point {
  int id;
  T x, y;
  Point(int id, T x, T y) : id(id), x(x), y(y) {}
  Point operator-(const Point &p) const {
    return {0, x - p.x, y - p.y};
  }
  bool operator<(const Point &p) const {
    return make_pair(x, y) < make_pair(p.x, p.y);
  }
  TT cross(const Point &p) const {
    return (TT)x * p.y - (TT)y * p.x;
  }
};
template<typename T>
int sign(T x) {
  return (T(0) < x) - (x < T(0));
}
// Check if p1p3 is on the left of p1p2
int orient(const Point &p1, const Point &p2, const Point &p3) {
  return sign((p2 - p1).cross(p3 - p1));
}

void test_case() {
  int n;
  cin >> n;
  n *= 3;

  vector<Point> v;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    v.push_back(Point(i + 1, x, y));
  }

  do {
    int i0 = -1;
    for (int i = 0; i < n; i++) {
      if (i0 == -1 or v[i] < v[i0]) i0 = i;
    }

    int i1 = -1;
    for (int i = 0; i < n; i++) {
      if (i != i0 and (i1 == -1 or orient(v[i0], v[i], v[i1]) == 1)) {
        i1 = i;
      }
    }

    int i2 = -1;
    for (int i = 0; i < n; i++) {
      if (i != i0 and i != i1 and (i2 == -1 or orient(v[i0], v[i], v[i2]) == 1)) {
        i2 = i;
      }
    }

    cout << v[i0].id << " " << v[i1].id << " " << v[i2].id << "\n";

    vector<Point> nv;
    for (int i = 0; i < n; i++) {
      if (i != i0 and i != i1 and i != i2) {
        nv.push_back(v[i]);
      }
    }
    swap(v, nv);

    n -= 3;
  } while (!v.empty());
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}