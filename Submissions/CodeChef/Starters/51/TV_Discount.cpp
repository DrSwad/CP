#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  if (a - c == b - d) cout << "Any\n";
  if (a - c < b - d) cout << "First\n";
  if (a - c > b - d) cout << "Second\n";
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