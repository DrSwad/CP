#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector<int> l(rows, -1), r(rows, -1);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'W') {
        if (l[row] == -1) l[row] = col;
        r[row] = col;
      }
    }
  }

  int at_row = 0, at_col = 0, dir = 1;
  int moves = 0;

  while (true) {
    bool should_stop = true;
    for (int row = at_row + 1; row < rows; row++) {
      if (l[row] != -1) {
        should_stop = false;
        break;
      }
    }
    {
      int col = at_col + dir;
      while (0 <= col and col < cols) {
        if (grid[at_row][col] == 'W') {
          should_stop = false;
          break;
        }
        col += dir;
      }
    }

    if (should_stop) break;

    int nxt_col = at_col;
    int col = at_col + dir;
    while (0 <= col and col < cols) {
      if (grid[at_row][col] == 'W' or (at_row + 1 < rows and grid[at_row + 1][col] == 'W')) {
        nxt_col = col;
      }
      col += dir;
    }

    if (nxt_col != at_col) {
      moves += abs(nxt_col - at_col);
      at_col = nxt_col;
    }
    else {
      moves++;
      at_row++;
      dir *= -1;
    }
  }

  cout << moves << "\n";

  return 0;
}