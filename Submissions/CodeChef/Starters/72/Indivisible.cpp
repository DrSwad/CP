#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, c;
  cin >> a >> b >> c;

  for (int k = 1; k <= 100; k++) {
    if (a % k != 0 and b % k != 0 and c % k != 0) {
      cout << k << "\n";
      return;
    }
  }
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