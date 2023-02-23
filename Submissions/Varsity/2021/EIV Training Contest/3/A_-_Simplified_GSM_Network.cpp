#include <bits/stdc++.h>
using namespace std;

void test_case(int b, int c, int r, int q) {
  vector<pair<double, double>> bts(b);
  for (auto &[x, y] : bts) cin >> x >> y;

  vector<pair<double, double>> city(c);
  for (auto &[x, y] : city) cin >> x >> y;

  auto road_switches = [&]() {};

  vector<vector<int>> e(c);
  while (r--) {
    int u, v;
    cin >> u >> v;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int cs = 1; ; cs++) {
    int b, c, r, q;
    cin >> b >> c >> r >> q;
    if (b == 0) break;
    cout << "Case " << cs << ":\n";
    test_case(b, c, r, q);
  }

  return 0;
}