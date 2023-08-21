#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (string &row : grid) cin >> row;

  int dim = max(rows, cols);
  vector freq(dim, vector(2, map<char, int>()));
  vector remain(rows, vector(cols, true));

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int c = grid[row][col] - 'a';
      freq[row][0][c]++;
      freq[col][1][c]++;
    }
  }

  auto remove =
    [&](int row, int col) {
      int c = grid[row][col] - 'a';
      remain[row][col] = false;
      assert(freq[row][0].find(c) != freq[row][0].end());
      freq[row][0][c]--; if (freq[row][0][c] == 0) freq[row][0].erase(c);
      assert(freq[col][1].find(c) != freq[col][1].end());
      freq[col][1][c]--; if (freq[col][1][c] == 0) freq[col][1].erase(c);
    };

  while (true) {
    queue<pair<int, int>> q;

    for (int row = 0; row < rows; row++) {
      if (freq[row][0].size() == 1 and freq[row][0].begin()->second > 1) {
        q.emplace(row, 0);
      }
    }

    for (int col = 0; col < cols; col++) {
      if (freq[col][1].size() == 1 and freq[col][1].begin()->second > 1) {
        q.emplace(col, 1);
      }
    }

    if (q.empty()) break;

    while (!q.empty()) {
      auto [index, type] = q.front();
      q.pop();

      if (type == 0) {
        int row = index;
        for (int col = 0; col < cols; col++) {
          if (remain[row][col]) remove(row, col);
        }
      }
      if (type == 1) {
        int col = index;
        for (int row = 0; row < rows; row++) {
          if (remain[row][col]) remove(row, col);
        }
      }
    }
  }

  int ans = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      ans += remain[row][col];
    }
  }

  cout << ans << "\n";

  return 0;
}