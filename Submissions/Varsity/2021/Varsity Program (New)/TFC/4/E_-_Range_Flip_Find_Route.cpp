#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int H, W;
  cin >> H >> W;

  vector<string> grid(H);
  for (auto &row : grid) cin >> row;

  vector<vector<int>> dp(H, vector<int>(W, H + W));

  for (int i = H - 1; i >= 0; i--) {
    for (int j = W - 1; j >= 0; j--) {
      if (i == H - 1 and j == W - 1) {
        dp[i][j] = grid[i][j] == '#';
      }
      if (i < H - 1) {
        int curr = dp[i + 1][j];
        if (grid[i + 1][j] != grid[i][j] and grid[i][j] == '#') curr++;
        dp[i][j] = min(dp[i][j], curr);
      }
      if (j < W - 1) {
        int curr = dp[i][j + 1];
        if (grid[i][j + 1] != grid[i][j] and grid[i][j] == '#') curr++;
        dp[i][j] = min(dp[i][j], curr);
      }
    }
  }

  cout << dp[0][0] << "\n";

  return 0;
}