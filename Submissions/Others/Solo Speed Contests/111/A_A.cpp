#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string a, b, c;
  cin >> a >> b >> c;
  if (a.back() == b[0] and b.back() == c[0]) cout << "YES\n";
  else cout << "NO\n";
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