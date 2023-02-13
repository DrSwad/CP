#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int L = 0, R = 1e9;
  while (L != R) {
    int mid = (L + R + 1) / 2;
    if (6ll * mid * mid <= n) L = mid;
    else R = mid - 1;
  }

  int x = L;
  if (6ll * x * x >= n) cout << (3 * x) << "\n";
  else if (6ll * x * x + 4ll * x >= n) cout << (3 * x + 1) << "\n";
  else if (6ll * (x + 1) * (x + 1) - 4ll * (x + 1) >= n) cout << (3 * x + 2) << "\n";
  else cout << (3 * x + 3) << "\n";
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