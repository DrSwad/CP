#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  int x, y;
  cin >> x >> y;
  int p = (x + y) % 2;

  bool ans = true;
  while (k--) {
    int x, y;
    cin >> x >> y;

    if ((x + y) % 2 == p) ans = false;
  }

  if (ans) cout << "YES\n";
  else cout << "NO\n";
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