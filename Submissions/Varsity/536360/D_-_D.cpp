#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int x, y;
  cin >> x >> y;

  int x1, y1, x2, y2;
  int a = abs(x) + abs(y);
  if (x < 0) {
    x1 = -a, y1 = 0, x2 = 0;
    y2 = y > 0 ? a : -a;
  }
  else {
    x1 = 0, x2 = a, y2 = 0;
    y1 = y > 0 ? a : -a;
  }

  cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}