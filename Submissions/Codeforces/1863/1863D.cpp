#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (auto &row : grid) cin >> row;

  vector<int> row_cnt(rows, 0), col_cnt(cols, 0);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'L' or grid[row][col] == 'R') {
        col_cnt[col]++;
      }
      if (grid[row][col] == 'U' or grid[row][col] == 'D') {
        row_cnt[row]++;
      }
    }
  }

  for (int row = 0; row < rows; row++) {
    if (row_cnt[row] % 2 != 0) {
      cout << "-1\n";
      return;
    }
  }

  for (int col = 0; col < cols; col++) {
    if (col_cnt[col] % 2 != 0) {
      cout << "-1\n";
      return;
    }
  }

  vector<string> ans(rows, string(cols, '.'));
  for (int col = 0; col < cols; col++) {
    int cnt = 0;
    for (int row = 0; row < rows; row++) {
      if (grid[row][col] == 'L') {
        if (cnt & 1) ans[row][col] = 'W', ans[row][col + 1] = 'B';
        else ans[row][col] = 'B', ans[row][col + 1] = 'W';
        cnt++;
      }
    }
  }
  for (int row = 0; row < rows; row++) {
    int cnt = 0;
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == 'U') {
        if (cnt & 1) ans[row][col] = 'W', ans[row + 1][col] = 'B';
        else ans[row][col] = 'B', ans[row + 1][col] = 'W';
        cnt++;
      }
    }
  }

  for (auto row : ans) cout << row << "\n";
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