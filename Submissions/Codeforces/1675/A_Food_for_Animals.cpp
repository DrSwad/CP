#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int df, cf, cc;
  int dn, cn;
  cin >> df >> cf >> cc >> dn >> cn;
  dn = max(0, dn - df);
  cn = max(0, cn - cf);
  cout << (cc >= dn + cn ? "YES" : "NO") << "\n";
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