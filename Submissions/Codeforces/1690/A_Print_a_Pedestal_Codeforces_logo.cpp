#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int L = 0, R = n;
  while (R - L > 1) {
    int m = (L + R) / 2;
    if (m + (m - 1) + (m - 2) >= n) R = m;
    else L = m;
  }

  int v1 = R;
  n -= v1;

  int v2 = min(n - 1, v1 - 1);
  n -= v2;

  int v3 = n;

  cout << v2 << " " << v1 << " " << v3 << "\n";
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