#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int x, y;
  cin >> x >> y;

  if (n == 1) {
    if (x != y) cout << "NO\n";
    else cout << "YES\n";
  }
  else {
    if ((x & y) != y) cout << "NO\n";
    else {
      int z = x ^ y;
      int cnt = __builtin_popcount(z);
      if (n > (1 << cnt)) cout << "NO\n";
      else cout << "YES\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}