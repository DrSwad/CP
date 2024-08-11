#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int xc, yc, k;
  cin >> xc >> yc >> k;

  if (k & 1) cout << xc << " " << yc << "\n", k--;

  while (k) {
    cout << xc - k / 2 << " " << yc - k / 2 << "\n";
    cout << xc + k / 2 << " " << yc + k / 2 << "\n";
    k -= 2;
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