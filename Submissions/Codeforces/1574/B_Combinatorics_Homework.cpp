#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, c, m;
  cin >> a >> b >> c >> m;

  if (a > c) swap(a, c);
  if (b > c) swap(b, c);

  if (a + b + c - 3 < m or a + b < c - m) cout << "NO\n";
  else cout << "YES\n";
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