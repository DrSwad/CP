#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, a, b, s;
  cin >> n >> a >> b >> s;

  cout << ((a * (n - 1) + b <= s and s <= a + b * (n - 1)) ? "YES" : "NO") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}