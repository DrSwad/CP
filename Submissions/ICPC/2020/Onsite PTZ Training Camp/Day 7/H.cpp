#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector<vector<vector<int>>> grundy(rows, vector(cols, vector<int>(3, -1)));

  for (int row = rows - 1; row >= 0; row--) {
    for (int col = cols - 1; col >= 0; col--) {
      if (grid[row][col] == '#') continue;
      vector<bool> grundy_vis(4, false);
    }
  }

  int ans = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'B') {
        ans ^= grundy[row][col][2];
      }
    }
  }

  cout << (ans ? "Alice" : "Bob") << "\n";

  return 0;
}