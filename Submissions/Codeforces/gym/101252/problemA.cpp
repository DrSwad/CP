#include <bits/stdc++.h>
using namespace std;

int dr[] = { 0, -1,  0, +1};
int dc[] = {+1,  0, -1,  0};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector grid(rows, vector<int>(cols));
  for (int row = 0; row < rows; row++) {
    string s;
    cin >> s;
    for (int col = 0; col < cols; col++) {
      grid[row][col] = s[col] - '0';
    }
  }

  vector vis(rows, vector(cols, false));

  int ans = 0;
  int row = 0, col = 0;
  int dir = 0;

  string moves;
  cin >> moves;

  for (char move : moves) {
    if (move == 'L') (dir += 1) %= 4;
    else if (move == 'R') (dir += 3) %= 4;
    else {
      int new_row = row + dr[dir];
      int new_col = col + dc[dir];

      if (new_row == row) {
        int cell_col = min(col, new_col);
        for (int cell_row : {row, row - 1}) {
          if (0 <= cell_row and cell_row < rows) {
            if (vis[cell_row][cell_col]) ans += grid[cell_row][cell_col] / 2;
            else ans += grid[cell_row][cell_col], vis[cell_row][cell_col] = true;
          }
        }
      }
      else {
        int cell_row = min(row, new_row);
        for (int cell_col : {col, col - 1}) {
          if (0 <= cell_col and cell_col < cols) {
            if (vis[cell_row][cell_col]) ans += grid[cell_row][cell_col] / 2;
            else ans += grid[cell_row][cell_col], vis[cell_row][cell_col] = true;
          }
        }
      }

      swap(row, new_row);
      swap(col, new_col);
    }
  }

  cout << ans << "\n";

  return 0;
}