#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int x, k;
  cin >> x >> k;
  cout << 2 * x << " " << 1ll * (x * k) * (x * k - 1) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}