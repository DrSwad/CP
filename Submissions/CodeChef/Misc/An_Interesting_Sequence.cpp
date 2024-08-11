/*

   gcd(k + i * i, 2 * i + 1)

   If i is even, i = 2 * x, 1 <= x <= k:
   = gcd(k + 4 * x * x, 4 * x + 1)
   = gcd(k - x, 4 * x + 1)
   = gcd(4 * k - 4 * x, 4 * x + 1)
   = gcd(4 * k + 1, 4 * x + 1)

   If i is odd, i = 2 * x - 1, 1 <= x <= k:
   = gcd(k + 4 * x * x - 4 * x + 1, 4 * x - 1)
   = gcd(k + x, 4 * x - 1)
   = gcd(4 * k + 4 * x, 4 * x - 1)
   = gcd(4 * k + 1, 4 * x - 1)

 */

#include <bits/stdc++.h>
using namespace std;

void test_case() {}

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