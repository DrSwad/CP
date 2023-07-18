#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, d, h;
  cin >> n >> d >> h;

  vector<int> y(n);
  for (int &i : y) cin >> i;

  double area = (double)d * h / 2;
  double ans = 0;

  for (int i = 0; i < n; i++) {
    ans += area;
    if (i < n - 1 and y[i + 1] - y[i] < h) {
      int cur_h = h - (y[i + 1] - y[i]);
      double r = (double)h / cur_h;
      double extra_area = area / (r * r);
      ans -= extra_area;
    }
  }

  cout << fixed << setprecision(10) << ans << "\n";
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