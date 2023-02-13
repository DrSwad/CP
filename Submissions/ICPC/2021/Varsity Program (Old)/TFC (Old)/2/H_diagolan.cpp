#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<bool>> grid(n, vector<bool>(n, false));
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    grid[x][y] = true;
  }

  vector<int> row_ones(n, 0);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      row_ones[x] += grid[x][y];
    }
  }

  vector<tuple<int, int, int>> moves;
  for (int at_row = 0, at_column = 0; at_row < n; at_row++) {
    int min_row = -1;
    for (int x = at_row; x < n; x++) {
      if (min_row == -1 or row_ones[x] < row_ones[min_row]) {
        min_row = x;
      }
    }

    for (int i = at_column; i < n; i++) {
      if (grid[min_row][i]) {
        for (int x = at_row; x < n; x++) {
          row_ones[x] -= grid[x][i];
          swap(grid[x][at_column], grid[x][i]);
        }
        if (at_column != i) moves.push_back({2, at_column, i});
        at_column++;
      }
    }

    if (at_row != min_row) moves.push_back({1, at_row, min_row});
    swap(grid[min_row], grid[at_row]);
    swap(row_ones[min_row], row_ones[at_row]);
  }

  cout << moves.size() << "\n";
  for (auto [t, i1, i2] : moves) {
    cout << t << " " << i1 + 1 << " " << i2 + 1 << "\n";
  }

  return 0;
}