#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int rows, cols;
  cin >> rows >> cols;

  int ans = min(rows + 1, cols);
  vector grid(rows, vector(cols, 0));

  if (cols == 1) {
    ans = 0;
    for (int row = 0; row < rows; row++) {
      grid[row][0] = 0;
    }
  }
  else {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        int zero_at = 1 + (row % (cols - 1));
        int dist = col - zero_at;
        if (dist < 0) dist += cols;
        grid[row][col] = dist;
      }
    }
  }

  cout << ans << "\n";
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (col) cout << " ";
      cout << grid[row][col];
    }
    cout << "\n";
  }
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