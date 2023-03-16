#include <bits/stdc++.h>
using namespace std;

void test_case() {
  double k;
  cin >> k;

  double ans = sqrt(3 / (4 - k * k) - 1);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(4);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
