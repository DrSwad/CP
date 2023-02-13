#include <bits/stdc++.h>
using namespace std;

double dist(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> x(9), y(9);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int v;
      cin >> v;
      v--;
      x[v] = i;
      y[v] = j;
    }
  }

  double ans = 0;
  for (int v = 0; v < 8; v++) {
    ans += dist(x[v], y[v], x[v + 1], y[v + 1]);
  }

  cout << fixed << setprecision(10) << ans << "\n";

  return 0;
}