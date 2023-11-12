#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<string> grid(2);
  cin >> grid[0] >> grid[1];

  vector<tuple<int, int, int>> empty_blocks;

  for (int row = 0; row < 2; row++) {
    for (int l = 0; l < n; ) {
      int r = l;
      while (r < n and grid[row][r] == '.') r++;

      int len = r - l;
      if (len) empty_blocks.emplace_back(len, row, l);

      l = r + 1;
    }
  }

  sort(empty_blocks.begin(), empty_blocks.end());

  function<void(int, int)> fill_up_horizontally =
    [&](int row, int col) {
      assert(grid[row][col] == '.');
      grid[row][col] = 'X';
      for (int i = col + 1; i < n and grid[row][i] == '.'; i++) {
        grid[row][i] = 'X';
      }
      for (int i = col - 1; i >= 0 and grid[row][i] == '.'; i--) {
        grid[row][i] = 'X';
      }
    };

  int ans = 0;
  for (auto [len, row, l] : empty_blocks) {
    if (grid[row][l] == 'X') continue;
    ans++;
    fill_up_horizontally(row, l);
    if (len == 1 and grid[row ^ 1][l] == '.') {
      fill_up_horizontally(row ^ 1, l);
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
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}