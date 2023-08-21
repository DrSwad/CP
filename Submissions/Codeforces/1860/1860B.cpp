#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int m, k, a1, ak;
  cin >> m >> k >> a1 >> ak;

  int q = m / k;
  int r = m % k;

  int ans = 0;
  if (a1 < r) {
    r -= a1;
    ans = r;
    ans += max(0, q - ak);
  }
  else {
    a1 -= r;
    if (q > ak) {
      q -= ak;
      q -= a1 / k;
      ans += max(0, q);
    }
  }
  cout << ans << "\n";
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