#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> grid(2, vector<int>(n));
  for (auto &row : grid) for (int &i : row) cin >> i;

  long long ans = 0;
  vector<int> carry(2, 0);

  for (int col = 0; col < n; col++) {
    for (int row = 0; row < 2; row++) {
      ans += abs(carry[row]);
      carry[row]++;
    }
    // use grid[row][col]
    for (int row = 0; row < 2; row++) {
      carry[row] -= grid[row][col];
    }
    // use carry[row] in carry[row ^ 1]
    for (int row = 0; row < 2; row++) {
      if (carry[row] < 0 and carry[row ^ 1] > 0) {
        int take = min(-carry[row], carry[row ^ 1]);
        carry[row] += take;
        carry[row ^ 1] -= take;
        ans += take;
      }
    }
  }

  assert(carry[0] == 0 and carry[1] == 0);
  cout << ans << "\n";

  return 0;
}