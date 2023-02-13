#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;
  n = abs(n);

  if (n % 3 == 0) cout << n / 3 << "\n";
  else if (n % 3 == 2) cout << n / 3 + 1 << "\n";
  else {
    if (n == 1) cout << "2\n";
    else cout << n / 3 + 1 << "\n";
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