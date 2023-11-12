#include <bits/stdc++.h>
using namespace std;

const int dr[] = {+1, 0, -1, 0};
const int dc[] = {0, +1, 0, -1};

void test_case() {
  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector<vector<bool>> vis;
  function<void(int, int)> dfs =
    [&](int row, int col) {
      vis[row][col] = true;
      for (int dir = 0; dir < 4; dir++) {
        int nrow = row + dr[dir];
        int ncol = col + dc[dir];
        if (0 <= nrow and nrow < rows and
            0 <= ncol and ncol < cols and
            !vis[nrow][ncol] and
            (grid[row][col] == '.' or grid[row][col] == grid[nrow][ncol])
        ) {
          dfs(nrow, ncol);
        }
      }
    };

  string ans = "NO";

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == '.') {
        grid[row][col] = 'B';

        vis = vector(rows, vector(cols, false));
        for (int row = 0; row < rows; row++) {
          for (int col = 0; col < cols; col++) {
            if (grid[row][col] == '.') {
              dfs(row, col);
            }
          }
        }

        grid[row][col] = '.';

        for (int row = 0; row < rows; row++) {
          for (int col = 0; col < cols; col++) {
            if (grid[row][col] == 'W' and !vis[row][col]) {
              ans = "YES";
            }
          }
        }
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}