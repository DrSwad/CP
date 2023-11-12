#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  vector right(rows, vector(cols, 0));
  for (int row = 0; row < rows; row++) {
    for (int col = cols - 1; col >= 0; col--) {
      if (col == cols - 1) right[row][col] = 1;
      else if (grid[row][col] != grid[row][col + 1]) right[row][col] = 1;
      else right[row][col] = 1 + right[row][col + 1];
    }
  }

  int ans = 0;

  for (int col = 0; col < cols; col++) {
    multiset<int> ms;
    for (int up_row = 0, down_row = 0; down_row < rows; down_row++) {
      ms.insert(right[down_row][col]);
      while (down_row - up_row + 1 > *ms.begin()) {
        ms.erase(ms.find(right[up_row++][col]));
      }
      ans = max(ans, down_row - up_row + 1);
    }
  }

  cout << ans * ans << "\n";

  return 0;
}