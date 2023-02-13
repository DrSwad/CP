#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> grid(2, vector<int>(n, 0));
  for (auto &row : grid) {
    for (int &cell : row) cin >> cell, cell++;
  }
  grid[0][0] = 0;

  vector<vector<int>> fwd(2, vector<int>(n, INT_MIN));
  vector<vector<int>> bck(2, vector<int>(n, INT_MIN));
  for (int row = 0; row < 2; row++) {
    for (int col = n - 1; col >= 0; col--) {
      int curr_fwd = ((n - 1) - col) + grid[row][col];
      fwd[row][col] = col == n - 1 ? curr_fwd : max(fwd[row][col + 1], curr_fwd);
      int curr_bck = (col - 0) + grid[row][col];
      bck[row][col] = col == n - 1 ? curr_bck : max(bck[row][col + 1], curr_bck);
    }
  }

  int time = 0;
  int ans = INT_MAX;

  for (int col = 0, row = 0; col < n; col++, time++) {
    time = max(time, grid[row][col]);
    int nrow = row ^ 1;

    {
      int ntime = max(time + ((n - 1) - col), fwd[row][col]);
      ntime++;
      ntime = max(ntime + ((n - 1) - 0), bck[nrow][col]) - (col - 0);
      ans = min(ans, ntime);
    }

    time++;
    row = nrow;
    time = max(time, grid[row][col]);
  }

  ans = min(ans, time - 1);
  cout << ans << "\n";
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