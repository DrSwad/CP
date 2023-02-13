#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> c(4, 0);
  while (n--) {
    int x, y;
    cin >> x >> y;
    if (x == 0) {
      if (y <= 0) c[0] = max(c[0], abs(y));
      else c[1] = max(c[1], abs(y));
    }
    else {
      if (x <= 0) c[2] = max(c[2], abs(x));
      else c[3] = max(c[3], abs(x));
    }
  }

  cout << 2 * accumulate(c.begin(), c.end(), 0) << "\n";
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