#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<string> grid(n);
  for (string &row : grid) cin >> row;

  int tot1 = 0;
  for (string &row : grid) {
    tot1 += count(row.begin(), row.end(), '1');
  }

  bool flag = false;
  int mn1 = 3;

  for (int i = 0; i < n; i++) {
    for (int di = 0; di < 2; di++) {
      int dx = di * 2 - 1;
      int ni = i + dx;
      if (ni < 0 or n <= ni) continue;
      for (int j = 0; j < m; j++) {
        for (int dj = 0; dj < 2; dj++) {
          int dy = dj * 2 - 1;
          int nj = j + dy;
          if (nj < 0 or m <= nj) continue;
          if (grid[i][j] == '0' and grid[ni][j] == '0') flag = true;
          if (grid[i][j] == '0' and grid[i][nj] == '0') flag = true;

          int cnt1 = (grid[i][j] - '0') + (grid[ni][j] - '0') + (grid[i][nj] - '0');
          mn1 = min(mn1, cnt1);
        }
      }
    }
  }

  if (flag) cout << tot1 << "\n";
  else cout << tot1 - mn1 + 1 << "\n";
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