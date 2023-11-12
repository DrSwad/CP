#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector wolf_taken(rows, vector(cols, false));
  int dr[4] = {-1, 0, +1, 0};
  int dc[4] = {0, -1, 0, +1};
  int ans = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'P') {
        for (int dir = 0; dir < 4; dir++) {
          int nrow = row + dr[dir];
          int ncol = col + dc[dir];
          if (0 <= nrow and nrow < rows and
              0 <= ncol and ncol < cols and
              grid[nrow][ncol] == 'W' and
              !wolf_taken[nrow][ncol]
          ) {
            wolf_taken[nrow][ncol] = true;
            ans++;
          }
        }
      }
    }
  }

  cout << ans << "\n";

  return 0;
}