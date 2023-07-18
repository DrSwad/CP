#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int w, a, b;
  cin >> w >> a >> b;

  if (a + w < b) cout << b - (a + w) << "\n";
  else if (b + w < a) cout << a - (b + w) << "\n";
  else cout << 0 << "\n";
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