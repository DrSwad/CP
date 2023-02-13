#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n, R;
    scanf("%d %d %d", &m, &n, &R);

    vector<vector<int>> a(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) { scanf("%d", &a[i][j]); }
    }

    int ans = 0;
    for (int j = 0; j < n; j++) {
      int sum = 0;
      for (int i = 1; i <= m; i++) {
        sum += (max(a[i][j], a[i][j + 1]) + R - 1) / R;
      }
      ans = max(ans, sum);
    }

    printf("%d\n", ans);
  }

  return 0;
}