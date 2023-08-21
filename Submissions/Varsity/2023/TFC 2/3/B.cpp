#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int rows, cols;
  cin >> rows >> cols;

  vector grid(rows, vector(cols, 0));
  for (auto &row : grid) {
    for (int &cell : row) cin >> cell;
  }

  vector<pair<int, int>> order;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      order.emplace_back(row, col);
    }
  }

  sort(
    order.begin(),
    order.end(),
    [&](const pair<int, int> &cell1, const pair<int, int> &cell2) {
      return grid[cell1.first][cell1.second] > grid[cell2.first][cell2.second];
    }
  );

  vector visited(rows, vector(cols, false));
  const int dr[] = {+1, 0, -1, 0};
  const int dc[] = {0, +1, 0, -1};

  function<void(int, int)> dfs =
    [&](int row, int col) {
      if (visited[row][col]) return;
      visited[row][col] = true;

      for (int dir = 0; dir < 4; dir++) {
        int nrow = row + dr[dir];
        int ncol = col + dc[dir];
        if (0 <= nrow and nrow < rows and
            0 <= ncol and ncol < cols and
            grid[nrow][ncol] <= grid[row][col]
        ) {
          dfs(nrow, ncol);
        }
      }
    };

  int ans = 0;
  for (auto [row, col] : order) {
    if (!visited[row][col]) {
      ans++;
      dfs(row, col);
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
    test_case();
  }

  return 0;
}