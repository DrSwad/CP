#include <bits/stdc++.h>
using namespace std;

const int MX = 100;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<tuple<int, int, int, int>> rects(n);
  for (auto & [x0, x1, y0, y1] : rects) {
    cin >> x0 >> x1 >> y0 >> y1;
  }

  int ans = 0;
  for (int x = 0; x <= MX; x++) {
    for (int y = 0; y <= MX; y++) {
      bool covered = false;
      for (auto [x0, x1, y0, y1] : rects) {
        if (x0 <= x and x < x1 and y0 <= y and y < y1) {
          covered = true;
          break;
        }
      }
      ans += covered;
    }
  }

  cout << ans << "\n";

  return 0;
}