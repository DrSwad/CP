#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  for (int mask = 0; mask < 1 << n; mask++) {
    if (__builtin_popcount(mask) != (n + 1) / 2) continue;

    int g = 0;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        g = gcd(g, a[i]);
      }
    }

    if (g == 2) {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";
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