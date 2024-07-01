#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> grid(2, vector<int>(n, 0));

  long long ans = 0;

  for (int i = 0; i < 2 * n; i++) {
    int x, y;
    cin >> x >> y;

    if (x < 1) ans += 1 - x, x = 1;
    if (x > n) ans += x - n, x = n;
    if (y < 1) ans += 1 - y, y = 1;
    if (y > 2) ans += y - 2, y = 2;

    grid[y - 1][x - 1]++;
  }

  vector<int> carry(2, 0);
  for (int col = 0; col < n; col++) {
    for (int row = 0; row < 2; row++) {
      ans += abs(carry[row]);
      carry[row]++;
    }
    for (int row = 0; row < 2; row++) {
      carry[row] -= grid[row][col];
    }
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