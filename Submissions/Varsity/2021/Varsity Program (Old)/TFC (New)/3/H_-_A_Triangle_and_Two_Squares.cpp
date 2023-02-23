#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, x, y;
  cin >> a >> b >> x >> y;
  if (a == b) cout << "no\n";
  else {
    int Y = a - min(x, min(y, min(a - b - x, a - b - y)));
    cout << (a * b <= Y * (a - b) ? "yes" : "no") << "\n";
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