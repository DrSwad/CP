#include <bits/stdc++.h>
using namespace std;

const int MX = 4e4;

void test_case() {
  int l, r;
  cin >> l >> r;

  long long ans = LLONG_MAX;
  for (int g = 1; g <= MX; g++) {
    int x = 1 + (l - 1) / g;
    int a = g * x;
    int b = a + g;
    if (l <= a and b <= r) {
      ans = min(ans, 1ll * a * b / g);
    }
  }
  for (int x = 1; x <= MX; x++) {
    int g = 1 + (l - 1) / x;
    int a = g * x;
    int b = a + g;
    if (l <= a and b <= r) {
      ans = min(ans, 1ll * a * b / g);
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