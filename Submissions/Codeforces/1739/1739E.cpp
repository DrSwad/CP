#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int rows = 2;
  int cols;
  cin >> cols;

  vector<string> grid(rows);
  cin >> grid[0] >> grid[1];

  vector dirts(rows, vector<int>());
  int tot_dirts = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (grid[row][col] == '1') {
        dirts[row].push_back(col);
        tot_dirts++;
      }
    }
  }

  const int inf = 2 * cols + 1;
  vector dp(rows, vector(cols, vector(3, inf)));

  function<int(int, int, array<int, 2>)> DP =
    [&](int row, int col, array<int, 2> cleared) {
      assert(cleared[row] == col);
      assert(abs(cleared[row] - cleared[row ^ 1]) <= 1);

      if (col >= cols) return 0;

      int &cdp = dp[row][col][cleared[row ^ 1] - col + 1];
      if (cdp != inf) return cdp;

      if (cleared[row ^ 1] < col and grid[row ^ 1][col] == '1') {
        array<int, 2> nxt_cleared;
        nxt_cleared[row ^ 1] = max(cleared[row ^ 1], col);
        nxt_cleared[row] = max(cleared[row], col + 1);

        int add = col + 1 < cols and cleared[row] < col + 1 and grid[row][col + 1] == '1';
        cdp = min(cdp, DP(row ^ 1, col, nxt_cleared) + add);
      }

      if (col + 1 < cols and cleared[row] < col + 1 and grid[row][col + 1] == '1') {
        array<int, 2> nxt_cleared;
        nxt_cleared[row ^ 1] = max(cleared[row ^ 1], col);
        nxt_cleared[row] = max(cleared[row], col + 1);

        int add = cleared[row ^ 1] < col and grid[row ^ 1][col] == '1';
        cdp = min(cdp, DP(row, col + 1, nxt_cleared) + add);
      }

      {
        array<int, 2> nxt_cleared;
        nxt_cleared[row ^ 1] = max(cleared[row ^ 1], col);
        nxt_cleared[row] = max(cleared[row], col + 1);

        int add = col + 1 < cols and cleared[row] < col + 1 and grid[row][col + 1] == '1';
        add += cleared[row ^ 1] < col and grid[row ^ 1][col] == '1';
        int got = DP(row, col + 1, nxt_cleared);
        cdp = min(cdp, got + add);
      }

      return cdp;
    };

  cout << tot_dirts - DP(0, 0, {0, -1}) << "\n";

  return 0;
}