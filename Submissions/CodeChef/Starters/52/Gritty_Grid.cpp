#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;

  x &= 1;
  y &= 1;
  bool same = (((n - 1) + (m - 1)) & 1) == 0;
  bool ans;

  if (!x and !y) ans = same;
  if (x and !y) ans = true;
  if (!x and y) ans = true;
  if (x and y) ans = !same;

  cout << (ans ? "Yes" : "No") << "\n";
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