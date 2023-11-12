#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_COORD = 3e6 + 5;

int rows, cols;
int grid[MAX_COORD];

ll solve(const vector<vector<int>> &square_grid) {
  int rows = square_grid.size();
  int cols = square_grid[0].size();
  int diag_dim = rows + cols - 1;

  vector diag_grid(diag_dim, vector<int>(diag_dim, 0));

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int diag_row = row + col;
      int diag_col = col - row + rows;
      diag_grid[diag_row][diag_col] = square_grid[row][col];
    }
  }

  vector pref_diag_grid(diag_dim, vector<ll>(diag_dim, 0));

  for (int diag_row = 0; diag_row < diag_dim; diag_row++) {
    for (int diag_col = 0; diag_col < diag_dim; diag_col++) {
      pref_diag_grid[diag_row][diag_col] = diag_grid[diag_row][diag_col];
      if (diag_row) {
        pref_diag_grid[diag_row][diag_col] += pref_diag_grid[diag_row - 1][diag_col];
      }
      if (diag_col) {
        pref_diag_grid[diag_row][diag_col] += pref_diag_grid[diag_row][diag_col - 1];
      }
      if (diag_row and diag_col) {
        pref_diag_grid[diag_row][diag_col] -= pref_diag_grid[diag_row - 1][diag_col - 1];
      }
    }
  }

  function<ll(int, int, int)> diag_square =
    [&](int row1, int col1, int side_len) {
      int row2 = row1 + side_len - 1;
      int col2 = col1 + side_len - 1;
      ll ret = pref_diag_grid[row2][col2];
      if (row1) ret -= pref_diag_grid[row1 - 1][col2];
      if (col1) ret -= pref_diag_grid[row2][col1 - 1];
      if (row1 and col1) ret += pref_diag_grid[row1 - 1][col1 - 1];
      return ret;
    };

  ll ans = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int max_dist = min(row, min(col, min(rows - 1 - row, cols - 1 - col)));
      int diag_row = row + (col - max_dist);
      int diag_col = (col - max_dist) - row + rows;
      ans = max(ans, diag_square(diag_row, diag_col, 2 * max_dist + 1));
    }
  }

  return ans;
}

ll go(int center_row, int center_col) {
  ll cur = 0;
  int max_dist = min(center_row, min(center_col, min(rows - 1 - center_row, cols - 1 - center_col)));

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (abs(row - center_row) + abs(col - center_col) <= max_dist) {
        cur += grid[row * cols + col];
      }
    }
  }

  ll ans = cur;

  while ((++center_col) + max_dist < cols) {
    for (int row = center_row - max_dist; row <= center_row + max_dist; row++) {
      int col_dist = max_dist - abs(center_row - row);
      cur += grid[row * cols + center_col + col_dist];
      cur -= grid[row * cols + center_col - col_dist - 1];
    }
    ans = max(ans, cur);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> rows >> cols;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (rows <= cols) cin >> grid[row * cols + col];
      else cin >> grid[col * rows + row];
    }
  }
  if (rows > cols) swap(rows, cols);

  ll ans = 0;

  vector square_grid(rows, vector<int>(rows));

  {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < rows; col++) {
        square_grid[row][col] = grid[row * cols + col];
      }
    }
    ans = max(ans, solve(square_grid));
  }

  {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < rows; col++) {
        square_grid[row][col] = grid[row * cols + col + (cols - rows)];
      }
    }
    ans = max(ans, solve(square_grid));
  }

  ans = max(ans, go((rows - 1) / 2, (rows - 1) / 2));
  if (rows % 2 == 0) {
    ans = max(ans, go((rows - 1) / 2 + 1, (rows - 1) / 2));
  }

  cout << ans << "\n";

  return 0;
}