#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int x1, x2, x3, x4, h;
  cin >> x1 >> x2 >> x3 >> x4 >> h;

  if (x2 < x3 or x4 < x1) cout << "0\n";
  else cout << (min(x2, x4) - max(x1, x3)) * 1ll * h << "\n";
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