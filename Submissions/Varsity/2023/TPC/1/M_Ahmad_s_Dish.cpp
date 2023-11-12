#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

double circle_area(int r) {
  return PI * r * r;
}

double regular_poly_area(int n, int l) {
  double center_angle = 2 * PI / n;
  double r = l / 2.0 / sin(center_angle / 2);
  return n * r * r * sin(center_angle) / 2;
}

void test_case() {
  int r, n, l;
  cin >> r >> n >> l;
  // debug((97.147392059793 - circle_area(r)) / regular_poly_area(n, l));
  cout << circle_area(r) + 9 * regular_poly_area(n, l) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}