#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, c;
  cin >> a >> b >> c;

  cout << max(0, max(b, c) + 1 - a) << " " << max(0, max(a, c) + 1 - b) << " " << max(0, max(a, b) + 1 - c) << "\n";
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