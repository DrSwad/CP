#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<pair<int, int>> points(n);
  for (auto & [x, y] : points) cin >> x >> y;

  auto is_right_angle = [&](pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    auto [x3, y3] = p3;
    long long d12 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    long long d13 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
    long long d23 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
    return d12 == d13 + d23
           or d13 == d12 + d23 or
           d23 == d12 + d13;
  };

  while (q--) {
    int qx, qy;
    cin >> qx >> qy;

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        ans += is_right_angle(points[i], points[j], make_pair(qx, qy));
        if (is_right_angle(points[i], points[j], make_pair(qx, qy))) {
          cerr << i << " " << j;
        }
      }
    }

    cout << ans << "\n";
  }

  return 0;
}