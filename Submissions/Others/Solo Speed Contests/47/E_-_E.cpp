#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> info(n);
  for (auto & [x, y, h] : info) cin >> x >> y >> h;

  for (int cx = 0; cx <= 100; cx++) {
    for (int cy = 0; cy <= 100; cy++) {
      int ch = -1;
      int mn = INF;
      bool flag = true;

      for (auto [x, y, h] : info) {
        int d = abs(x - cx) + abs(y - cy);
        if (h == 0) mn = min(mn, d);
        else {
          int _ch = h + d;
          if (ch != -1 and ch != _ch) flag = false;
          ch = _ch;
        }
      }

      if (flag and mn >= 1 and mn >= ch and (ch == -1 or ch >= 1)) {
        cout << cx << " " << cy << " " << ch << "\n";
        return 0;
      }
    }
  }

  assert(false);

  return 0;
}