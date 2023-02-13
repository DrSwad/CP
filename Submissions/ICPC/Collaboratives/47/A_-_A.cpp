#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
  double x, y;
  PT() { x = 0, y = 0; }
  PT(double x, double y) : x(x), y(y) {}
};

// starting point as and direction vector ad
bool ray_ray_intersection(PT as, PT ad, PT bs, PT bd) {
  double dx = bs.x - as.x, dy = bs.y - as.y;
  double det = bd.x * ad.y - bd.y * ad.x;
  if (fabs(det) < eps) return 0;
  double u = (dy * bd.x - dx * bd.y) / det;
  double v = (dy * ad.x - dx * ad.y) / det;
  if (sign(u) >= 0 && sign(v) >= 0) return 1;
  else return 0;
}

void test_case() {}

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