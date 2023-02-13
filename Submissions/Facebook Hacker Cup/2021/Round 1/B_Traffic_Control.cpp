#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;

  if (a < n + m - 1 or b < n + m - 1) {
    cout << "Impossible\n";
    return;
  }

  cout << "Possible\n";

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (i == n and j == 1) cout << b - (n + m - 2);
      else if (i == n and j == m) cout << a - (n + m - 2);
      else cout << "1";

      if (j == m) cout << "\n";
      else cout << " ";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}